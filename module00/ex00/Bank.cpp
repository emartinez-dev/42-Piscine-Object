/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bank.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:53:51 by franmart          #+#    #+#             */
/*   Updated: 2024/10/25 21:40:46 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bank.hpp"

class	Bank::AccountNotFoundError: public std::exception
{
	virtual const char *what() const throw()
	{
		return ("<AccountNotFoundError> The account was not found at this bank\n");
	}
};

class	Bank::NoEnoughFondsError: public std::exception
{
	virtual const char *what() const throw()
	{
		return ("<NoEnoughFondsError> The account doesn't have enough fonds to withdraw "
				"the amount requested\n");
	}
};

class	Bank::NoEnoughLiquidityError: public std::exception
{
	virtual const char *what() const throw()
	{
		return ("<NoEnoughLiquidityError> The bank doesn't have enough liquidity for the "
		 		"loan requested\n");
	}
};

class	Bank::CantCloseActiveLoanError: public std::exception
{
	virtual const char *what() const throw()
	{
		return ("<CantCloseActiveLoanError> The account doesn't have enough balance to cancel"
				"the loan\n");
	}
};

class	Bank::BankIsFullError: public std::exception
{
	virtual const char *what() const throw()
	{
		return ("<BankIsFullError> The bank cannot add new clients\n");
	}
};

Bank::Bank():_liquidity(0),_next_id(0), _accounts()
{
}

Bank::~Bank()
{
	if (_accounts.empty())
		return ;

	std::map<long, Account*>::iterator	it = _accounts.begin();
	while (it != _accounts.end())
	{
		delete it->second;
		it++;
	}
}

Bank::Bank(Bank const &copy):_liquidity(copy._liquidity), _next_id(copy._next_id),
							_accounts(copy._accounts)
{
}

Bank	&Bank::operator=(const Bank &copy)
{
	if (this != &copy) {
		this->_next_id = copy._next_id;
		this->_liquidity = copy._liquidity;
		this->_accounts = copy._accounts;
	}
	return *this;
}

long	Bank::create_account()
{
	if (_next_id == __LONG_MAX__ && _accounts.find(_next_id) != _accounts.end())
		throw BankIsFullError();

	Account *acc = new Account(_next_id);

	_accounts[_next_id] = acc;
	_next_id++;
	return _next_id - 1;
}

bool	Bank::remove_account(long id)
{
	std::map<long, Account*>::iterator	it = _accounts.find(id);

	if (it == _accounts.end())
		throw AccountNotFoundError();

	Account	*acc = it->second;

	if (acc->get_balance() < acc->get_debt())
		throw CantCloseActiveLoanError();

	_liquidity -= (acc->get_balance() * 0.05);
	_liquidity += acc->get_debt();

	delete it->second;
	_accounts.erase(it->first);
	return (true);
}

bool	Bank::modify_account(long id, long amount)
{
	std::map<long, Account*>::iterator	it = _accounts.find(id);

	if (it == _accounts.end())
		throw AccountNotFoundError();

	Account	*acc = it->second;
	long	old_balance = acc->get_balance();

	_liquidity -= (old_balance * 0.05);
	acc->set_balance(amount);
	_liquidity += (acc->get_balance() * 0.05);
	return (true);
}

long	Bank::deposit(long id, long amount)
{
	std::map<long, Account*>::iterator	it = _accounts.find(id);

	if (it == _accounts.end())
		throw AccountNotFoundError();

	Account	*acc = it->second;

	acc->add_amount(amount);
	_liquidity += (amount * 0.05);
	return (acc->get_balance());
}

long	Bank::withdraw(long id, long amount)
{
	std::map<long, Account*>::iterator	it = _accounts.find(id);

	if (it == _accounts.end())
		throw AccountNotFoundError();

	Account	*acc = it->second;

	if (acc->get_balance() < amount)
		throw NoEnoughFondsError();

	_liquidity -= (amount * 0.05);
	acc->withdraw_amount(amount);
	return (acc->get_balance());
}

long	Bank::loan(long id, long amount)
{
	if (amount > _liquidity)
		throw NoEnoughLiquidityError();

	std::map<long, Account*>::iterator	it = _accounts.find(id);

	if (it == _accounts.end())
		throw AccountNotFoundError();

	Account	*acc = it->second;
	acc->loan_amount(amount);
	_liquidity -= amount;
	return (acc->get_balance());
}

long	Bank::get_liquidity() const
{
	return (_liquidity);
}

long	Bank::get_accounts_number() const
{
	return (_accounts.size());
}

const Account	&Bank::get_account(long id) const
{
	std::map<long, Account*>::const_iterator	it = _accounts.find(id);

	if (it == _accounts.end())
		throw AccountNotFoundError();

	const Account &acc = *it->second;
	return (acc);
}

std::ostream &operator<<(std::ostream &os, const Bank &obj)
{
	long i = 0;
	long max = obj.get_accounts_number();

	os << "Bank informations : " << std::endl;
	os << "Liquidity : " << obj.get_liquidity() << std::endl;
	while (i < max)
	{
		try {
			os << obj.get_account(i) << std::endl;
		}
		catch (Bank::AccountNotFoundError &exception) {
			;
		}
		i++;
	}
	return (os);
}