/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bank.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:53:49 by franmart          #+#    #+#             */
/*   Updated: 2024/10/25 21:38:38 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BANK_HPP
#define BANK_HPP

# include "Account.hpp"

# include <iostream>
# include <map>

class Bank
{
	private:
		long	_liquidity;
		long	_next_id;
		std::map<long, Account*>	_accounts;

	public:
		Bank();
		~Bank();
		Bank(Bank const &copy);
		Bank	&operator=(Bank const &copy);

		long	create_account();
		bool	remove_account(long id);
		bool	modify_account(long id, long amount);

		long	deposit(long id, long amount);
		long	withdraw(long id, long amount);

		long	loan(long id, long amount);

		long			get_liquidity() const;
		long			get_accounts_number() const;
		const Account	&get_account(long id) const;

		class	AccountNotFoundError;
		class	NoEnoughFondsError;
		class	NoEnoughLiquidityError;
		class	CantCloseActiveLoanError;
		class	BankIsFullError;
};

std::ostream &operator<<(std::ostream &os, const Bank &obj);

#endif