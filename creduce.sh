# ORIGINAL TEMPLATE
#########################################################################################
#! /bin/bash 

# step 1: make sure #ifdef is retained
grep -q "#ifdef WITH_COMPILE_ERROR" hello.cpp || exit 1
# step 2: make sure code is still valid C++ code
clang++ -c -std=c++17 hello.cpp || exit 1
# step 3: make sure the code fails only with -DWITH_COMPILE_ERROR and has the expected compilation error
compile_output=$(clang++ -c -std=c++17 hello.cpp -DWITH_COMPILE_ERROR 2>&1)
if [[ $compile_output == *"error: cannot assign to return value because function 'operator[]' returns"* ]]; then
    echo "Still fails with compile error"
    exit 0
fi
# otherwise, the reduction is not interesting
exit 1

# SIMLPFIED clang crash
#########################################################################################
clang-20 "-cc1" "-triple" "x86_64-unknown-linux-gnu"  "f.cpp"  |& grep "visitBUILD_VECTOR" 

# SIMPIFLIED APP Runtime crash
#########################################################################################
#! /bin/bash 
clang -c -O3 app.c
compile_output=$(./a.out 2>&1)
if [[ $compile_output == *"floating overflow"* ]]; then
    echo "App Fails"
    exit 0
fi
exit 1
