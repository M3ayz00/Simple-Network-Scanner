/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NetworkScanner.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:48:38 by msaadidi          #+#    #+#             */
/*   Updated: 2024/10/25 15:36:22 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETWORKSCANNER_HPP
#define NETWORKSCANNER_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sstream>

class   NetworkScanner
{
    private :
        std::string IpStart;
        std::string IpEnd;
        std::vector<std::string>    results;

    public  :
        NetworkScanner();
        NetworkScanner(const std::string& _IpStart, const std::string& _IpEnd);
        ~NetworkScanner();
        NetworkScanner(const NetworkScanner& N);
        NetworkScanner& operator=(const NetworkScanner& N);
        void    pingHost(std::string& Ip);
        void    scanPort(std::string& Ip, int port);
        int     calcPortion(std::string& sIp, std::string& eIp);
        void    outputResults();
        void    scanNetwork();
};

#endif 