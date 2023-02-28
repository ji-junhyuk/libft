/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:49:24 by junji             #+#    #+#             */
/*   Updated: 2023/02/27 20:52:29 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <iostream>

void exec_add(PhoneBook &phoneBook)
{
    phoneBook.Add();
	return ;
}

void exec_search(PhoneBook &phoneBook)
{
    phoneBook.Search();
	return ;
}

void exec_exit(PhoneBook &phoneBook)
{
    (void)phoneBook;
    system("leaks PHONEBOOK");
    exit(0);
}

void exec_else(PhoneBook &phoneBook)
{
    (void)phoneBook;
	std::cout << "유효한 명령어가 아닙니다.\n";
	return ;
}

int main(void)
{
    PhoneBook phonebook;
	std::string cmd;
	int	key;
	void (*fp[4])(PhoneBook &phoneBook) = {exec_add, exec_search, exec_exit, exec_else};
	std::string str[3] = {"ADD", "SEARCH", "EXIT"};

	while (true)
	{
        std::cout << "명령어를 입력해주세요: 1. ADD 2. SEARCH 3. EXIT\n";
		std::getline(std::cin, cmd);
        if (std::cin.eof())
            break ;
		key = 3;
		for (int i = 0; i < 3; i++)
		{
			if (str[i] == cmd)
				key = i;
		}
		fp[key](phonebook);
	}
}
