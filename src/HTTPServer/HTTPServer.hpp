/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 23:56:30 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/27 11:00:49 by dmartiro         ###   ########.fr       */
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
		virtual uint32_t getIp( void ) const;
		virtual uint16_t getPort( void ) const;
    public:
        void pushLocation(std::string const &prefix, Location locationDirective);
    public:
        const Location *find(std::string const &prefix) const;
        Location *find(std::string const &prefix);

    private:
        std::vector<std::string> ServerName;
    private:
        std::map<int, Client> clnt;                     // [Clients]
        std::map<std::string, Location> locations;      // <prefix, LocationDirective>  location / {Location}
};
#endif