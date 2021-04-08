#!/bin/bash
if [ $# -ne 1 ]; then
  echo "$#"
  exit 1
fi

BASE_DIR=$1
SHARED_LIB="libTP-HW2-LIB-PAR.so"
SEQ_STRESS_TEST="TP-HW2-STRESS-SEQ"
PAR_STRESS_TEST="TP-HW2-STRESS-PAR"
ARTIFACTS_PATH="${BASE_DIR}/artifacts"
SEEDS=(123 777 42)
#ARRAYS_SIZES=(10 1000 2500000 250000000 1000000000)
ARRAYS_SIZES=(10 1000)

for ARR_SIZE in ${ARRAYS_SIZES[*]}; do
  echo -e "\n\n::Array size: ${ARR_SIZE}::"
  for SEED in ${SEEDS[*]}; do
    PAR_RESULT=$("${ARTIFACTS_PATH}"/${PAR_STRESS_TEST} "$SEED" "$ARR_SIZE" "${ARTIFACTS_PATH}"/${SHARED_LIB})
    PAR_RESULT=(${PAR_RESULT//\n/ }) # split to array
    SEQ_RESULT=$("${ARTIFACTS_PATH}"/${SEQ_STRESS_TEST} "$SEED" "$ARR_SIZE")
    SEQ_RESULT=(${SEQ_RESULT//\n/ })
    TIME_DIFF="$(echo "${SEQ_RESULT[0]}"-"${PAR_RESULT[0]}" | bc)" # using bc for floating point arithmetic
    TIME_DIFF=${TIME_DIFF#-} # remove the minus sign
    echo -e "Implementation time: \n\tParallel: ${PAR_RESULT[0]}\n\tSequence: ${SEQ_RESULT[0]}"
    echo -e "Time diff: $TIME_DIFF"
    if [ "${SEQ_RESULT[1]}" == "${SEQ_RESULT[1]}" ]; then
      echo -e "Results are the same: ${SEQ_RESULT[1]}\n"
    else
      echo -e "The results vary! \n\tParallel: ${PAR_RESULT[1]}\n\tSequence: ${SEQ_RESULT[1]}\n"
      echo "Stress test FAILED :("
      exit 1
    fi
  done
done

echo "Stress test SUCCESSFUL :)"
exit 0