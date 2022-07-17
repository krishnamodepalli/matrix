
#include <stdio.h>

int a, b, c, d; // Orders of all matrices. (a, b) -> matrix A, (c, d) -> matrix B.
int add(int *A, int *B); // Function to add 2 matrices.
int sub(int *A, int *B); // Function to subtract 2 matrices.
int mul(int *A, int *B); // Function to multiply 2 matrices.
int transpose(int A[a][b]); // Function to find transpse of a matrix.
int det(int a, int A[a][a]); // Function to find the determinant of a matrix.
int power(int); //Function used by det(..) matrix to get accurate results.
// Mainly to when we multiply (-1)^(i+j) in finding determinant of a matrx.

int main()
{
	int choice, outcome; // Choice variable to let user choose from options & outcome to recieve the function reeturn-values.
	printf("1 . Addition\n2 . Subtraction\n3 . Multiplication\n4 . Determinant\n5 . Transpose\n");
	printf("Enter your choice : ");
	scanf("%d", &choice); // Reading the choice variable.
	if (choice == 1 || choice == 2 || choice == 3) // Condition check if `choice` either 1 or 2 or 3.
	{
	orders_error:
		if (choice == 1) // If addition or
			printf("Note: For addition, orders of both matrices should be same.\n");
		else if (choice == 2) // subtraction orders must be same.
			printf("Note: For subtraction, orders of both matrices should be same.\n");
		else // Else, for multiplication no. of columns of 1st matrix == no. of rows of 2nd matrix.
			printf("Note: For Multiplication, no. of columns of 1st matrix == no. of rows of 2nd matrix.\n");
		printf("Enter the order of 1st matrix : "); // Reading order of 1st matrix.
		scanf("%d%d", &a, &b);
		printf("Enter the order of 2nd matrix : "); // Reading order of 2nd matrix.
		scanf("%d%d", &c, &d);

		if (((choice == 1 || choice == 2) && ((a != c) || (b != d))) || ((choice == 3) && (b != c))){
			// Checking if orders are in correct way.
			printf("You are mistaken in entering the orders of matrices.\n");
			goto orders_error; //If not redirecting the user to type in the orders once again.
		}

		int A[a][b], B[c][d]; // Declaring both the matrices.
		printf("Enter the 1st matrix :\n"); // Reading 1st matrix.
		for (int i = 0; i < a; i++)
		{
			for (int j = 0; j < b; j++)
				scanf("%d", *(A+i*b+j)); // NOTE: Scaning through pointers.
		}
		printf("Enter the 2nd matrix :\n"); // Reading 2nd matrix.
		for (int i = 0; i < c; i++)
		{
			for (int j = 0; j < d; j++)
				scanf("%d", *(A+i*d+j)); // NOTE: Scaning through pointers.
		}
		// Redirecting to corrosponding function.
		if (choice == 1)
			outcome = add(*A, *B);
		else if (choice == 2)
			outcome = sub(*A, *B);
		else
			outcome = mul(*A, *B);
		if (outcome == 0) // Returning 0 if all functions returned 0.
		{
			printf("Every thing has run perfrectly.\nAll operations are completed.\n");
			return 0;
		}
		// Else, returning 1.
		printf("Something went wrong.\n");
		return 1;
	}
	else if (choice == 4 || choice == 5) // Else if choice is either 4 or 5.
	{

		printf("Note: Determinant or Transpose or Inverse is calculated for only square matrix.\n");
		printf("Enter the (n x n) n value : "); // Determinant, Transpose, Inverse is calculated for only square matrix.
		scanf("%d", &a);
		b = a;
		printf("Enter the matrx :\n");
		int A[a][b]; // Declaring the Matrix.
		for (int i = 0; i < a; i++) // Reading the matrix.
		{
			for (int j = 0; j < b; j++)
				scanf("%d", &A[i][j]);
		}
		if (choice == 4){
			outcome = det(a, A); // Calling det() function.
			printf("Determinant : %d\n", outcome);
		}
		else if (choice == 5)
			transpose(A);
		printf("Every thing has run perfrectly.\nAll operations are completed.\n");
		return 0; // Returning 0.
	}
	else
	{
		printf("Invalid Input!!!\nStart the program again.");
		return 1;
	}
}

int add(int *A, int *B) // Function for addition.
{
	printf("Resultant matrix :\n");
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
			printf("%d ", *(A+i*b+j) + *(B+i*b+j)); // Printing the sum of 2 maatrices.
		printf("\n");
	}
	return 0;
}

int sub(int *A, int *B) // Function for Subtraction.
{
	printf("Resultant matrix :\n");
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
			printf("%d ", *(A+i*b+j) - *(B+i*b+j)); // Printing the difference of 2 matrices.
		printf("\n");
	}
	return 0;
}

int mul(int *A, int *B) // Function for multiplication.
{
	printf("Resultant matrix :\n");
	for (int i = 0; i < a; i++)
	{
		for (int j = 0, item; j < d; j++)
		{
			item = 0;
			for (int k = 0; k < b; k++)
				item += *(A+i*b+k)*(*(B+k*d+j));
			printf("%d ", item); // Calculating each element of resulatant matrix and printing it.
		}
		printf("\n");
	}
	return 0;
}

int det(int a, int A[a][a]) // Function for calculating determinant of a matrix.
{ // This is a recursive function. Because for 3x3 or more ordered matrix, we need all the dets of smaller sub-matrices of the matrix.
	if (a > 2)
	{
		int determinant = 0;
		int sub_matrix[a-1][a-1];
		for (int i = 0; i < a; i++)
		{
			for (int j = 0; j < a - 1; j++)
			{
				for (int k = 0; k < a - 1; k++)
					sub_matrix[j][k] = A[1+j][(i+1+k > a-1)?(i+1+k-a):(i+1+k)];
			}
			determinant += (a%2==0?power(i):1)*A[0][i]*det(a - 1, sub_matrix);
		}
		return determinant; // Returning the result to main().
	}
	return A[0][0]*A[1][1] - A[0][1]*A[1][0];
}

int transpose(int A[a][b])
{
	printf("Resultant matrix :\n");
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < a; j++)
		{
			if (j > i) // Selecting specific elements of matri for swaping
				A[j][i] = A[i][j] + A[j][i] - (A[i][j] = A[j][i]); // Swaping the elements of the matrix.
			printf("%d ", A[i][j]); // Printing each element regardless of checking the condition.
		}
		printf("\n");
	}
	return 0;
}

int power(int n)
// Function to help the det() funtion while calculating determinant.
{
	int result = 1;
	for (int i = 0; i < n; i++)
		result *= -1;
	return result;
}
