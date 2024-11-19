# Minimum_Cash_Flower
# Bank Transaction Management System

This C++ program manages bank transactions between multiple banks supporting various payment platforms.

## Implementation Details

- `Bank.h`: Header file containing the definition of the `bank` struct.
- `lib.h`: Header file containing necessary library imports.
- `minimumFinder`: Function to find the index of the bank with the minimum net amount.
- `Simple_Max_Index`: Function to find the index of the bank with the maximum net amount.
- `maximumFinder`: Function to find the index of the bank with the maximum net amount within the intersecting payment platforms.
- `Display`: Function to display the transactions.
- `minimize_cash_flower`: Function to minimize cash flow between banks.
- `main`: Entry point of the program.

## Usage

1. Enter the number of banks.
2. Provide the names of the banks and the number of transaction types supported by each bank.
3. Enter the types of transactions supported by each bank.
4. Input the number of transactions.
5. Enter the details of each transaction.
6. The program minimizes cash flow between banks and displays the transactions.

## Example Input
Enter the number of banks: 4
world Bank : World Bank
Enter the number of payment platforms supported by World Bank: 2
Enter the payment platforms supported by World Bank:
GPay PhonePe
Bank 2: Bank A
Enter the number of payment platforms supported by Bank A: 1
Enter the payment platforms supported by Bank A:
Slice
Bank 3: Bank B
Enter the number of payment platforms supported by Bank B: 1
Enter the payment platforms supported by Bank B:
PhonePe
Bank 4: Bank C
Enter the number of payment platforms supported by Bank C: 1
Enter the payment platforms supported by Bank C:
UPI
Enter the number of transactions: 4
Enter the transactions:
Enter the name of the bank and the transaction: World Bank Bank A 200
Enter the name of the bank and the transaction: Bank A Bank B 150
Enter the name of the bank and the transaction: Bank B Bank C 80
Enter the name of the bank and the transaction: Bank C World Bank 40

## Output

The program displays the transactions involved in minimizing cash flow between banks.

- Ensure proper input format and data integrity for accurate results.
- Adjust the input format and test cases as needed for comprehensive testing.
