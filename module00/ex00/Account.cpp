/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:53:56 by franmart          #+#    #+#             */
/*   Updated: 2024/10/25 21:41:48 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"

Account::Account():_id(0),_balance(0),_debt(0)
{
}

Account::Account(long id):_id(id),_balance(0),_debt(0)
{
}

Account::~Account()
{
}

Account::Account(Account const &copy):_id(copy._id),_balance(copy._balance),_debt(copy._debt)
{
}

Account	&Account::operator=(const Account &copy)
{
	if (this != &copy) {
		this->_id = copy._id;
		this->_balance = copy._balance;
		this->_debt = copy._debt;
	}
	return *this;
}

long	Account::add_amount(long amount)
{
	_balance += amount;
	return _balance;
}

long	Account::withdraw_amount(long amount)
{
	_balance -= amount;
	return _balance;
}

long	Account::loan_amount(long amount)
{
	_balance += amount;
	_debt += amount;
	return _balance;
}

long	Account::get_balance() const
{
	return _balance;
}

long	Account::get_debt() const
{
	return _debt;
}

long	Account::get_id() const
{
	return _id;
}

long	Account::set_balance(long amount)
{
	_balance = amount;
	return _balance;
}

std::ostream &operator<<(std::ostream &os, const Account &obj)
{
	os << "[ ID_" << obj.get_id() << " ] - [ Balance: " << obj.get_balance()
		<< " ] - [ Debt: " << obj.get_debt() << " ]";
	return (os);
}