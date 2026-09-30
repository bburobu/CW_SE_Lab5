#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

bool getmatrices(const std::string& filename, int& N, std::vector<double>& matrixA, std::vector<double>& matrixB){
    std::ifstream inputFile(filename);
    inputFile >> N;
    matrixA.resize(N * N);
    matrixB.resize(N * N);

    if (!inputFile.is_open()) {
            std::cerr << "Error: Could not open " << filename << std::endl;
            return false; 
        }

    for(int x = 0; x < N; ++x){
        for(int y = 0; y<N; ++y){
            inputFile >> matrixA[x*N+y];
        }
    }

    for(int x = 0; x < N; ++x){
        for(int y = 0; y<N; ++y){
            inputFile >> matrixB[x*N+y];
        }
    }
    inputFile.close();
    return true;
}

void showmatrix(const std::string& title, int N, const std::vector<double>& matrix){

    std::cout << "----" << title << "----" << std::endl;

    for(int x = 0; x < N; ++x){
        for(int y = 0; y<N; ++y){
            std::cout << std::setw(6) << matrix[x*N+y];
        }
        std::cout << "\n";
    }
}

void addmatrices(const std::string& title, int N, std::vector<double>& matrixA, std::vector<double>& matrixB){

    std::vector<double> matrixsum(N*N);
    

    for(int x = 0; x < N; ++x){
        for(int y = 0; y<N; ++y){
            matrixsum[x*N+y] = matrixA[x*N+y]+matrixB[x*N+y];
        }
    }
    
    showmatrix(title, N, matrixsum);
}

void dotmatrices(const std::string& title, int N, std::vector<double>& matrixA, std::vector<double>& matrixB){

    std::vector<double> matrixdot(N*N);
    

    for(int x = 0; x < N; ++x){
        for(int y = 0; y<N; ++y){
            double sum = 0.0;
            for (int k = 0; k < N; ++k) {
                sum += matrixA[x * N + k] * matrixB[k * N + y];
            }
            matrixdot[x*N+y] = sum;
        }
    }
    
    showmatrix(title, N, matrixdot);
}

void adddiagonal(const std::string& title, int N, std::vector<double>& matrixA, std::vector<double>& matrixB){

    double sum = 0;
    
    for(int k = 0; k < N; ++k){

        sum += matrixA[k*N+k]+matrixB[k*N+k];
    }
    std::cout << title << "\n\t" << sum << "\n";

    sum = 0.0;

    for(int k = 0; k < N; ++k){
        
        sum += matrixA[k*N+N-(k+1)]+matrixB[k*N+N-(k+1)];
        
    }
    std::cout << title << " 2\n\t" << sum << "\n";
}

void swaprows(const std::string& title, int N, std::vector<double>& matrixA, std::vector<double>& matrixB,int targetA,int targetB){
    
    double rowA[N];
    double rowB[N];
    std::vector<double> matrixswapA = matrixA;
    std::vector<double> matrixswapB = matrixB;
    
    if (0<= targetA && targetA <=N && 0 <= targetB && targetB <=N){
        for(int x = 0; x < N; ++x){
            rowA[x] = matrixA[targetA*N+x];
            rowB[x] = matrixB[targetB*N+x];
            }
        for(int x = 0; x < N; ++x){
            matrixswapB[targetB*N+x] = rowA[x];
            matrixswapA[targetA*N+x] = rowB[x];
            }
        
        showmatrix(title + "A", N, matrixswapA);
        showmatrix(title + "B", N, matrixswapB);
        }
}

void swapcols(const std::string& title, int N, std::vector<double>& matrixA, std::vector<double>& matrixB,int targetA,int targetB){
    
    double colA[N];
    double colB[N];
    std::vector<double> matrixswapA = matrixA;
    std::vector<double> matrixswapB = matrixB;
    
    if (0<=targetA && targetA <= N && 0 <= targetB && targetB <=N){
        for(int x = 0; x < N; ++x){
            colA[x] = matrixA[x*N+targetA];
            colB[x] = matrixB[x*N+targetB];
            }
        for(int x = 0; x < N; ++x){
            matrixswapB[x*N+targetB] = colA[x];
            matrixswapA[x*N+targetA] = colB[x];
            }
        
        showmatrix(title + "A", N, matrixswapA);
        showmatrix(title + "B", N, matrixswapB);
        }
}
void updateitem(const std::string& title, int N, std::vector<double>& matrix,int targetrow,int targetcol,int new_val){
    std::vector<double> new_matrix = matrix;
    if (0 <= targetrow && targetrow <= N && 0 <= targetcol && targetcol <= N){
        new_matrix[targetrow*N+targetcol] = new_val;
        showmatrix(title, N, new_matrix);
    }
}



int main(){
    std::string filename;
    

    std::cout << "Tell me the file name (or the path to the file) here: ";
    std::cin >> filename;

    
  
    //matrix variables/vectors
    int N;
    std::vector<double> matrixA(N*N);
    std::vector<double> matrixB(N*N);

    if (!getmatrices(filename, N, matrixA, matrixB)){
        std::cout << "error: could not read file. closing.";
        return 1;
    }
    

    showmatrix("Matrix A", N, matrixA);
    showmatrix("Matrix B", N, matrixB);

    addmatrices("Matrix A+B", N, matrixA, matrixB);

    dotmatrices("Matrix A*B",N, matrixA, matrixB);

    adddiagonal("Diagonal Sum", N, matrixA, matrixB);

    swaprows("Swap Rows: A = row 1, B = row 3: ", N, matrixA, matrixB, 0, 2);

    swapcols("Swap Columns: A = row 3, B = row 2: ", N, matrixA, matrixB, 2, 1);

    updateitem("Updated Matrix B item at row 2, column 1 to 104", N, matrixB, 1, 0, 104);


    return 0;
}