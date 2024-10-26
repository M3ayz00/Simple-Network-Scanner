/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NetworkScanner.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m3ayz00 <m3ayz00@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:48:38 by msaadidi          #+#    #+#             */
/*   Updated: 2024/10/26 16:05:23 by m3ayz00          ###   ########.fr       */
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
#include <thread>
#include <mutex>
#include <sstream>
#include <fcntl.h>

class   NetworkScanner
{
    private :
        std::string                 IpStart;
        std::string                 IpEnd;
        std::vector<std::string>    results;
        std::vector<int>            sOctets;
        std::vector<int>            eOctets;
        std::mutex                  resultsMutex;
        

    public  :
        NetworkScanner();
        NetworkScanner(const std::string& _IpStart, const std::string& _IpEnd);
        ~NetworkScanner();
        NetworkScanner(const NetworkScanner& N);
        NetworkScanner& operator=(const NetworkScanner& N);
        void    pingHost(const std::string& Ip);
        void    scanPorts(const std::string& Ip);
        void    calcPortion(const std::string& sIp, const std::string& eIp);
        void    outputResults();
        void    scanNetwork();
        void    scanIp(const std::string& Ip);
};

#endif 