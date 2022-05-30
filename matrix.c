
#include <stdio.h>

int a, b, c, d; // Orders of all matrices.
int add(int A[a][b], int B[c][d]); // Function to add 2 matrices.
int sub(int A[a][b], int B[c][d]); // Function to subtract 2 matrices.
int mul(int A[a][b], int B[c][d]); // Function to multiply 2 matrices.
int det(int a, int A[a][a]); // Function to find the determinant of a matrix.
int power(int); //Function used by det(..) matrix to get accurate results.
// Mainly to when we multiply (-1)^(i+j) in finding determinant of a matrx.

int main()
{
	int choice, outcome; // Choice variable to let user choose from options & outcome to recieve the function reeturn-values.
	printf("1 . Addition\n2 . Subtraction\n3 . Multiplication\n4 . Determinant\n");
	printf("Enter your choice : ");
	scanf("%d", &choice); // Reading the choice variable.
	if (choice == 1 || choice == 2 || choice == 3) // Condition check if `choice` either 1 or 2 or 3.
	{
	error:
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
			goto error; //If not redirecting the user to type in the orders once again.
		}

		int A[a][b], B[c][d]; // Declaring both the matrices.
		printf("Enter the 1st matrix :\n"); // Reading 1st matrix.
		for (int i = 0; i < a; i++)
		{
			for (int j = 0; j < b; j++)
				scanf("%d", &A[i][j]);
		}
		printf("Enter the 2nd matrix :\n"); // Reading 2nd matrix.
		for (int i = 0; i < c; i++)
		{
			for (int j = 0; j < d; j++)
				scanf("%d", &B[i][j]);
		}
		// Redirecting to corrosponding function.
		if (choice == 1)
			outcome = add(A, B);
		else if (choice == 2)
			outcome = sub(A, B);
		else
			outcome = mul(A, B);
		if (outcome == 0) // Returning 0 if all functions returned 0.
		{
			printf("Every thing has done perfrectly.\nAll operations are compleated.\n");
			return 0;
		}
		// Else, returning 1.
		printf("Something went wrong.\n");
		return 1;
	}
	else if (choice == 4) // Else if choice == 4,
	{
		printf("Note: Determinant is found for only square matrix.\n");
		printf("Enter the (n x n) n value : "); // Determinant is calculated for only square matrix.
		scanf("%d", &a);
		b = a;
		printf("Enter the matrx :\n");
		int A[a][b]; // Declaring the Matrix.
		for (int i = 0; i < a; i++) // Reading the matrix.
		{
			for (int j = 0; j < b; j++)
				scanf("%d", &A[i][j]);
		}
		outcome = det(a, A); // Calling det() function.
		printf("Determinant : %d\n", outcome);
		return 0; // Returning 0.
	}
}

int add(int A[a][b], int B[c][d])
{
	printf("Resultant matrix :\n");
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
			printf("%d ", A[i][j] + B[i][j]);
		printf("\n");
	}
	return 0;
}

int sub(int A[a][b], int B[c][d])
{
	printf("Resultant matrix :\n");
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
			printf("%d ", A[i][j] - B[i][j]);
		printf("\n");
	}
	return 0;
}

int mul(int A[a][b], int B[c][d])
{
	printf("Resultant matrix :\n");
	for (int i = 0; i < a; i++)
	{
		for (int j = 0, item; j < d; j++)
		{
			item = 0;
			for (int k = 0; k < b; k++)
				item += A[i][k]*B[k][j];
			printf("%d ", item);
		}
		printf("\n");
	}
	return 0;
}

int det(int a, int A[a][a])
{
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
		return determinant;
	}
	return A[0][0]*A[1][1] - A[0][1]*A[1][0];
}

int power(int n)
{
	int result = 1;
	for (int i = 0; i < n; i++)
		result *= -1;
	return result;
}
