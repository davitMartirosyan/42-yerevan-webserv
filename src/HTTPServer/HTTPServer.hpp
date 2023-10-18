/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 23:56:30 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/19 01:07:45 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPSERVER_HPP
#define HTTPSERVER_HPP
#include "Libs.hpp"

class Location
{
    public:
        Location( void );
        virtual ~Location();
    protected:
        std::string root;
        std::string path;
    protected:
        virtual std::string const &getRoot( void ) const = 0;
        virtual std::string const &getPath( void ) const = 0;
};


class HTTPServer : public Location
{
    public:
        HTTPServer( void );
        ~HTTPServer();
    private:
        int fd;
        int backlog;
        int autoindex;
    private:
        std::string listen;
        std::vector<std::string> server_names;
        std::string root;
        std::vector<std::string> locations;
        std::vector<std::string> index;
};

#endif