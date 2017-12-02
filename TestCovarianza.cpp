#include "Covarianza.h"

int main(){
	vector<double> v1 = {3, 3};
	vector<double> v2 = {4, 0};
	vector<double> v3 = {2, 3};
	//vector<double> v4 = {0, 1};

	Matriz v({
		v1,
		v2,
		v3
	});

	MatrizCovarianza MX = MatrizCovarianza(v);
	cout << MX.cov << "\n";

	pair<Matriz, vector<autovalor> > p = MX.Diagonalizar(2);

	std::cout << "Matriz V:" << std::endl;
	std::cout << p.first << std::endl;

	std::cout << "Vector diag:\n" << std::endl;
	for(int i = 0; i < p.second.size(); i++){
		std::cout << p.second[i];
		if(i != (p.second.size() - 1)){
			std::cout << ", ";
		}
		else{
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;

	return 0;
}