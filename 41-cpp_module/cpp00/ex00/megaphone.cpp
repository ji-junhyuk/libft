#include <iostream>

class Megaphone
{
	public:
		Megaphone(int argc, char *argv[])
		{
			if (argc == 1)
			{
				std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *\n";
				return ;
			}
			PrintUpper(argc, argv);
		};

	public:
		void PrintUpper(int argc, char *argv[])
		{
			for (int i = 1; i < argc; i++)
			{
				for (int j = 0; j < (int)strlen(argv[i]); j++)
				{
					if (argv[i][j] >= 'a' && argv[i][j] <= 'z')
						argv[i][j] = toupper(argv[i][j]);
				}
				std::cout << argv[i];
			}
		}
	
};

int main(int argc, char *argv[])
{
	Megaphone megaphone(argc, argv);
}
