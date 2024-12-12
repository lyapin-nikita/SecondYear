#include "formula.h"
#include <vector>


void TFormula::Input()
{
	std::cin >> _formula;
}

int TFormula::Checker()
{
	int res = 0;
	int index = 0;
	std::vector <int> firstColum;// (
	std::vector <int> secondColum;// )
	TStack <int> s;


	for (int i = 0; _formula[i] != '\0'; i++)
	{
		if (_formula[i] == '(')
		{
			index++;
			s.put(index);
		}
		if (_formula[i] == ')')
		{
			index++;
			if (!s.isEmpty())
			{
				firstColum.push_back(s.get());
				secondColum.push_back(index);
			}
			else
			{
				firstColum.push_back(0);
				secondColum.push_back(index);
				res++;
			}

		}
	}

	if (!s.isEmpty())
	{
		res += s.getDataCount();
		for (int i = s.getDataCount() - 1; i >= 0; i--)
		{
			firstColum.push_back(s.get());
			secondColum.push_back(0);
		}
	}


	std::cout << "Output table:" << '\n';
	for (int i = 0; i < firstColum.size(); i++)
	{
		std::cout << firstColum[i] << ' ' << secondColum[i] << "\n";
	}


	return res;
}

void TFormula::Converter()
{
	
}

double TFormula::Calculate()
{
	
}
