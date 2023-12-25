/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DefaultSetup.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:06:06 by dmartiro          #+#    #+#             */
/*   Updated: 2023/12/25 23:45:50 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFAULT_SETUP_HPP
#define DEFAULT_SETUP_HPP

#define READ_BUFFER             15000
#define WRITE_BUFFER            15000
#define DEFAULT_HTTP_PERM_PORT  "80"
#define DEFAULT_HTTP_PORT       "8080"
#define DEFAULT_MASK            "0.0.0.0"
#define CONFIGS "./conf/"
#define DFLT CONFIGS"webserv.conf"
#define HTTP_VERSION "HTTP/1.1"
#define DEFAULT_ROOT "/var/www/"
typedef int         sock_t;
#include "HTTPCoreException.hpp"
#endif