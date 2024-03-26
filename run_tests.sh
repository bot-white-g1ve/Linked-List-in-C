TESTDIR=$1

for input_file in "${TESTDIR}"/*.txt; do
    base_name=$(basename "$input_file" .txt)

    expected_output="${TESTDIR}/${base_name}.out"
    actual_output="${TESTDIR}/${base_name}.act"

    ./mtll < "$input_file" > "$actual_output"

    if diff -q "$actual_output" "$expected_output" >/dev/null; then
        echo "Test ${base_name} passed."
    else
        echo "Test ${base_name} failed. See differences below:"
        diff "$actual_output" "$expected_output"
    fi

    rm "$actual_output"
done