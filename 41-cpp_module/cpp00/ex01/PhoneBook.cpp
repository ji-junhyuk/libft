/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 20:23:10 by junji             #+#    #+#             */
/*   Updated: 2023/02/27 21:39:31 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook() : mCursor(0), mbFulled(false) {

}

void PhoneBook::Add() {
    if (mContacts[this->mCursor++].SetContact() == 1) {
        this->mCursor--;
    }
    if (this->mCursor == 8) {
        this->mbFulled = true;
    }
	this->mCursor %= CONTACT_MAX_SIZE;
}

void PhoneBook::Search() {
    if (this->mbFulled)
    {
        for (int i = 0; i < 8; ++i) {
            this->mContacts[i].ShowContactSummary(i);
        }
    }
    else
    {
        if (this->mCursor== 0)
            std::cout << "저장된 연락처가 없습니다.\n";
        for (int i = 0; i < this->mCursor; ++i) {
            this->mContacts[i].ShowContactSummary(i);
        }
    }
    ShowContact();
}

int PhoneBook::CheckValidNum(std::string &index) {
    int num;

    if (index.size() != 1 || !(index[0] >= '0' && index[0] <= '7'))
        return (1);
    num = atoi(index.c_str());
    if (!this->mbFulled && this->mCursor - 1 < num)
        return (1);
    this->mContacts[num].ShowContactDetail();
    return (0);
}

void PhoneBook::ShowContact() {
    std::string index;
    std::cout << "자세하게 확인 할 인덱스를 선택해주세요.\n";
    while (1) {
        std::getline(std::cin, index);
        if (!CheckValidNum(index)) {
            break;
        }
        std::cout << "유효하지 않은 입력입니다. 올바른 숫자를 입력해주세요\n > ";
    }
}

const Contact &PhoneBook::GetContact(int cursor) const {
    return this->mContacts[cursor];
}