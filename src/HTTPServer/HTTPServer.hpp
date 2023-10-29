/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 23:56:30 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/29 23:37:42 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPSERVER_HPP
#define HTTPSERVER_HPP
#include "Libs.hpp"
#include "../Location/Location.hpp"
#include "../Client/Client.hpp"
#include "../Tcp/Tcp.hpp"

class HTTPServer : public Tcp, public IListener, public ServerCore
{
    public:
        HTTPServer( void );
        ~HTTPServer();
        int getServerSocket( void );
    public: //ip port interface
		virtual void setPort(std::string const &port);
		virtual void setIp(std::string const &ipv);
		virtual const char* getIp( void ) const;
        virtual uint32_t getNIp( void ) const;
		virtual uint16_t getNPort( void ) const;
		virtual const char* getPort( void ) const;
    public:
        void pushLocation(std::string const &prefix, Location locationDirective);
    public:
        const Location *find(std::string const &prefix) const;
        Location *find(std::string const &prefix);
    private:
        std::vector<std::string> ServerName;
    private:
        std::map<sock_t, Client> clnt;                     // [Clients]
        std::map<std::string, Location> locations;      // <prefix, LocationDirective>  location / {Location}
};
#endif