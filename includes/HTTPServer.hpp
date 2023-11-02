/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 23:56:30 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/02 22:14:40 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPSERVER_HPP
#define HTTPSERVER_HPP
#include "Libs.hpp"
#include "Location.hpp"
#include "Client.hpp"
#include "Tcp.hpp"

class HTTPServer : public Tcp, public IListener, public ServerCore
{
    public:
        HTTPServer( void );
        ~HTTPServer();
    public:
		 void up( void );
    public: //ip port interface
		virtual void setPort(std::string const &port);
		virtual void setIp(std::string const &ipv);
		virtual const char* getIp( void ) const;
		virtual const char* getPort( void ) const;
        virtual uint32_t getNIp( void ) const;
		virtual uint16_t getNPort( void ) const;
    public:
        void push(std::string const &prefix, Location locationDirective);
        void push(sock_t clFd, Client &clt);
        void push(std::string const &srvName);
    public:
        const Location *find(std::string const &prefix) const;
        bool exist(sock_t fd);
        std::vector<std::string> const &getServerNames( void ) const;
    public:
        void request(Client &cl);
    private:
        std::vector<std::string> ServerName;
        std::map<sock_t, Client> clnt;                     // [Clients]
        std::map<std::string, Location> locations;      // <prefix, LocationDirective>  location / {Location}
};

#endif