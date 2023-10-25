/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 09:23:04 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/25 23:35:34 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_HPP
#define CORE_HPP
#include "Libs.hpp"

struct IListener
{
	protected:
		virtual void setIp(std::string const &ipv) = 0;
		virtual void setPort(std::string const &port) = 0;
		virtual uint32_t getIp( void ) const = 0;
		virtual uint16_t getPort( void ) const = 0;
	protected:
		uint32_t ip;
		uint16_t port;
};




#endif