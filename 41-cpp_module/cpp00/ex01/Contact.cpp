/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:45:17 by junji             #+#    #+#             */
/*   Updated: 2023/02/27 22:03:49 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"
#include <stdlib.h>

void Contact::SetFieldName()
{
    this->mFieldName[0] = "first name";
    this->mFieldName[1] = "last name";
    this->mFieldName[2] = "nickname";
    this->mFieldName[3] = "phone number";
    this->mFieldName[4] = "dark secret";
}

int Contact::SetContact()
{
    std::string buffer[FIELD_SIZE];
    SetFieldName();
    for (int i = 0; i < FIELD_SIZE; ++i)
    {
        std::cout << this->mFieldName[i] << " > ";
        std::getline(std::cin, buffer[i]);
        if (buffer[i].empty()) {
            return (1);
        }
        this->mPersonalInfo[i] = buffer[i];
    }
    return (0);
}

void Contact::ShowContactSummary(int cursor)
{
    std::string str;
    std::cout << "|";
    std::cout << std::setw(COLUMN_SIZE);
    std::cout << cursor;
    std::cout << "|";
    for (int i = 0; i < 3; ++i) {
        std::cout << std::setw(COLUMN_SIZE);
        if (mPersonalInfo[i].length() > COLUMN_SIZE) {
            str = mPersonalInfo[i].substr(0, COLUMN_SIZE);
            str[9] = '.';
            std::cout << str;
        }
        else {
            std::cout << mPersonalInfo[i];
        }
        std::cout << "|";
    }
    std::cout << '\n';
}

void Contact::ShowContactDetail() {
    for (int i = 0; i < FIELD_SIZE; ++i) {
        std::cout << this->mFieldName[i] << ": ";
        std::cout << mPersonalInfo[i] << '\n';
    }
}


