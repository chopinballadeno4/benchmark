#!/bin/zsh
set -eu

script_dir=${0:A:h}
out_dir=${script_dir}/out

mkdir -p "${out_dir}"

: "${IKOS_PREFIX:=/Users/baesungmin/ikos-install}"
: "${LLVM_PREFIX:=/opt/homebrew/opt/llvm@14}"

analysis_cxx_flags="-std=c++17 -D__IKOS__ \
    -I${script_dir}/include \
    -I${IKOS_PREFIX}/include"

sources=(
    src/fw_assert.cpp
    src/fw_format.cpp
    src/group_a.cpp
    src/group_b.cpp
    harness.cpp
)

# ── [1] Compile ───────────────────────────────────────────────────────────────
print "=== [1/5] Compile ==="
objects=()
for src in ${sources[@]}; do
    obj=${out_dir}/${src:t:r}.o
    IKOS_SCAN_NOTIFIER_FILES=1 \
        ${IKOS_PREFIX}/bin/ikos-scan-c++ \
        ${=analysis_cxx_flags} \
        -c ${script_dir}/${src} \
        -o ${obj}
    objects+=(${obj})
done

# ── [2] Link ──────────────────────────────────────────────────────────────────
print "=== [2/5] Link ==="
IKOS_SCAN_NOTIFIER_FILES=1 \
    ${IKOS_PREFIX}/bin/ikos-scan-c++ \
    ${objects[@]} \
    -o ${out_dir}/benchmark

# ── [3] Extract bitcode ───────────────────────────────────────────────────────
print "=== [3/5] Extract bitcode ==="
${IKOS_PREFIX}/bin/ikos-scan-extract \
    ${out_dir}/benchmark \
    -o ${out_dir}/benchmark.bc

# ── [4] Optimise (same passes as ref-harness) ─────────────────────────────────
print "=== [4/5] Optimise (mem2reg + gvn) ==="
${LLVM_PREFIX}/bin/opt \
    -passes='function(mem2reg,gvn)' \
    ${out_dir}/benchmark.bc \
    -o ${out_dir}/benchmark-opt.bc

# ── [5] IKOS analyse ──────────────────────────────────────────────────────────
print "=== [5/5] IKOS analyse ==="
all_analyses=boa,dbz,nullity,prover,upa,uva,sio,uio,shc,poa,pcmp,sound,fca,dca,dfa,dbg,watch
rm -f ${out_dir}/report.db ${out_dir}/report.txt
${IKOS_PREFIX}/bin/ikos \
    ${out_dir}/benchmark-opt.bc \
    -o ${out_dir}/report.db \
    -a=${all_analyses} \
    --proc=inter \
    --domain=interval \
    --display-checks=no \
    --status-filter='*' \
    --format=text \
    --report-file=${out_dir}/report.txt \
    --display-summary=full \
    --display-times=short \
    --color=no \
    --progress=no

grep ': error:'   ${out_dir}/report.txt > ${out_dir}/definite-errors.txt   || true
grep ': warning:' ${out_dir}/report.txt > ${out_dir}/warnings.txt          || true

print ""
print "=== Definite Errors ==="
cat ${out_dir}/definite-errors.txt || print "(none)"
print ""
print "=== Warnings ==="
cat ${out_dir}/warnings.txt || print "(none)"
print ""
print "=== Summary ==="
tail -20 ${out_dir}/report.txt
