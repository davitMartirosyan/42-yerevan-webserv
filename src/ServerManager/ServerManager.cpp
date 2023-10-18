/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 00:05:52 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/14 00:26:50 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerManager.hpp"

ServerManager::ServerManager(const char *config)
{
    std::cout << config << std::endl;
    srvsCount = 3; // իմիտացիա ենք անում յանի 3 հատ սերվերի դիրեկտիվ
                    // ենք քթել կոնֆիգ ֆայլում
}

ServerManager::~ServerManager()
{
    
}

void ServerManager::createServerInstances( void )
{
       
}