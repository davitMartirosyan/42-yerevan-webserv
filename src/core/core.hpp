/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 09:23:04 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/22 09:36:34 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_HPP
#define CORE_HPP
#include "Libs.hpp"

struct IListener
{
	protected:
		virtual void setListenerIpPort(std::string const &ip, std::string const &port) = 0;
		virtual std::string const &getIp( void ) const = 0;
		virtual std::string const &getPort( void ) const = 0;
		std::string ip;
		std::string port;
};




#endif