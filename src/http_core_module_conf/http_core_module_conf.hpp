/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http_core_module_conf.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 01:49:46 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/22 15:26:23 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_CORE_HPP
#define HTTP_CORE_HPP
#include "Libs.hpp"

struct http_core_module_conf
{
    public:
        std::string const &getRootPath( void );
        int getClientBodySize( void );
        void pushIndex(std::string const &fileNameExample);
        void pushMethods(std::string const &method);
    public:
        std::vector<std::string> getIndexeFiles( void ) const;
        
    protected:
    
        std::string root;                                       // [root]               www/server1/
        std::vector<std::string> index;                         // [index]              index.html barev.html index.htm ....
        std::vector<std::string> methods;                       // [allow_methods]      GET | POST | DELETE
        std::map<std::string, std::string> error_page;          // [error_page]         404 [root]/error_pages/404.html 
        bool autoindex;                                          // [autoindex]         on (true) | off (false)
        unsigned long long int client_body_size;                // [client_body_size]   200m -> 200.000.000byte -> 200mb
};

#endif