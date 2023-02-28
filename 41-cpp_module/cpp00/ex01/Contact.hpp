/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 20:18:01 by junji             #+#    #+#             */
/*   Updated: 2023/02/27 22:14:33 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>
#include <iomanip>

#define FIELD_SIZE 5
#define COLUMN_SIZE 10

class Contact
{
	private:
		std::string mPersonalInfo[FIELD_SIZE];
		std::string mFieldName[FIELD_SIZE];
	public:
		int SetContact();
        void SetFieldName();
        void ShowContactSummary(int cursor);
        void ShowContactDetail();
};

