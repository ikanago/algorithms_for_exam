# Algorithms for Exam

院試に出てきそうなアルゴリズムとデータ構造を C 言語で実装しました．

## Requirements
gcc
g++
make
cmake >= 3.0

## Set up
```bash
git clone https://github.com/ikanago/algorithms_for_exam.git
cd algorithms_for_exam
git submodule update -i # For thirdparty/googletest
cmake -B build
```

## Run Test
```bash
make -C build test -j # -j is optioanl for parallel compilation
```