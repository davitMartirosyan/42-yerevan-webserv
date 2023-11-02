/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DefaultSetup.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:06:06 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/29 23:31:01 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFAULT_HPP
#define DEFAULT_HPP

#define READ_BUFFER             150000
#define WRITE_BUFFER            150000
#define DEFAULT_HTTP_PERM_PORT  "80"
#define DEFAULT_HTTP_PORT       "8080"
#define DEFAULT_MASK            "0.0.0.0"
#define CONFIGS "./conf/"
#define DFLT CONFIGS"webserv.conf"
#include "../src/HTTPCoreException/HTTPCoreException.hpp"
#include "../src/ServerCore/ServerCore.hpp"
#include "../src/core/core.hpp"
typedef int sock_t;

#endif