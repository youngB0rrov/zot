#!/bin/bash

cd build

echo "Start running testing programm run_test..."
./TrigonometricApproximation

# �������� ��� �������� ��������� ����������� �������
if [ $? -ne 0]; then
	echo "Executing test programm failed"
	exit 1
fi

if [ -d "assets" ]; then
	echo "Test result are in assets directory"
	ls assets
else
	echo "Results of testing not found"
	exit 1
fi

echo "Testing completed successfully"

