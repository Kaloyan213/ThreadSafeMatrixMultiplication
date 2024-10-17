#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

const int SIZE = 10; 

void MultiplyRow(const std::vector<std::vector<int>>& A,
	const std::vector<std::vector<int>>& B,
	std::vector<std::vector<int>>& Result,
	int Row) 
{
	for (size_t j = 0; j < SIZE; j++)
	{
		for (size_t i = 0; i < SIZE; i++)
		{
			Result[Row][j] += A[Row][i] * B[i][j];
		}
	}
}

int main() {
	/*Creates a 4x4 matrix*/
	std::vector<std::vector<int>> A(SIZE, std::vector<int>(SIZE, 0));
	std::vector<std::vector<int>> B(SIZE, std::vector<int>(SIZE, 0));
	std::vector<std::vector<int>> Result(SIZE, std::vector<int>(SIZE, 0));

	for (size_t i = 0; i < SIZE; i++)
	{
		for (size_t j = 0; j < SIZE; j++)
		{
			A[i][j] = rand() % 10;
			B[i][j] = rand() % 10;
		}
	}

	std::vector<std::thread> Threads;
	for (size_t i = 0; i < SIZE; i++)
	{
		Threads.emplace_back(MultiplyRow, std::ref(A), std::ref(B), std::ref(Result), i);
		std::cout << "Thread with id: " << Threads[i].get_id() << " started.\n";
	}

	for (auto& t : Threads) {
		t.join();
	}


	// Display the result matrix C
	std::cout << "\n\nResulting Matrix C:\n";
	for (const auto& row : Result) {
		for (const auto& value : row) {
			std::cout << value << " ";
		}
		std::cout << "\n";
	}
}