#pragma once

#include "Contact.hpp"
#include <iostream>

#define CONTACT_MAX_SIZE 8

class PhoneBook
{
	private:
		Contact mContacts[CONTACT_MAX_SIZE];
		int		mCursor;
        bool    mbFulled;

	public:
		PhoneBook();
		void Add(void);
        void Search(void);
        const Contact &GetContact(int cursor) const;
        void ShowContact();
        int CheckValidNum(std::string &index);
};
