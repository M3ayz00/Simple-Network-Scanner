/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NetworkScanner.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:02:09 by msaadidi          #+#    #+#             */
/*   Updated: 2024/10/28 12:05:21 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NetworkScanner.hpp"

NetworkScanner::NetworkScanner(){}

NetworkScanner::NetworkScanner(const std::string& _IpStart, const std::string& _IpEnd) : IpStart(_IpStart), IpEnd(_IpEnd){}

NetworkScanner::~NetworkScanner(){}

NetworkScanner& NetworkScanner::operator=(const NetworkScanner& N)
{
    if (this == &N) return *this;
    IpStart = N.IpStart;
    IpEnd = N.IpEnd;
    return *this;
}

NetworkScanner::NetworkScanner(const NetworkScanner& N)
{
    *this = N;
}

void     NetworkScanner::calcPortion(const std::string& sIp, const std::string& eIp)
{
    std::istringstream   sStream(sIp), eStream(eIp);
    std::string         sByte, eByte;
    sOctets.clear();
    eOctets.clear();
    while (std::getline(sStream, sByte, '.') && std::getline(eStream, eByte, '.'))
    {
        sOctets.push_back(std::stoi(sByte));
        eOctets.push_back(std::stoi(eByte));
    }

}

int    NetworkScanner::pingHost(const std::string& Ip)
{
    std::string command = "ping -c 1 " + Ip + " > /dev/null 2>&1";
    int result = system(command.c_str());
    std::clog << "pinging the address : " + Ip << std::endl;
    if (!result)
        results.push_back(Ip + " is reachable");
    else
        results.push_back(Ip + " is not reachable");
    return (result);    
}

void    NetworkScanner::scanPort(const std::string& Ip, int port)
{
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0) 
    {
        results.push_back("Failed to create socket for " + Ip);
        return;
    }
    struct sockaddr_in  host_addr;
    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(port);
    inet_pton(AF_INET, Ip.c_str(), &host_addr.sin_addr);
    int result = connect(socketfd, (struct sockaddr *)&host_addr, sizeof(host_addr));
    std::clog << "connecting to port " << port << std::endl;
    if (!result)
        results.push_back("-> " + std::to_string(port) + " is open in " + Ip);
    else
        results.push_back("-> " + std::to_string(port) + " is closed in " + Ip);
    close(socketfd);

}


void    NetworkScanner::outputResults()
{
    std::cout << "------RESULTS------\n";
    for (size_t i = 0; i < results.size(); i++)
        std::cout << results[i] << std::endl;
}

void    NetworkScanner::scanIp(const std::string& Ip)
{
    if (!pingHost(Ip))
    {
        results.push_back("PORTS : ");
        scanPort(Ip, 22);
        scanPort(Ip, 88);
        scanPort(Ip, 443);
    }
}

void    NetworkScanner::scanNetwork()
{
    calcPortion(IpStart, IpEnd);
    std::vector<int>    currentOctet = sOctets;
    std::vector<std::thread> myThreads;
    std::clog << "SCANNING...\n";
    for (int thirdOctet = sOctets[2]; thirdOctet <= eOctets[2]; thirdOctet++)
    {
        currentOctet[2] = thirdOctet;
        int startFourthOctet = (thirdOctet == sOctets[2]) ? sOctets[3] : 0; 
        int endFourthOctet = (thirdOctet == eOctets[2]) ? eOctets[3] : 255;
        for (int fourthOctet = startFourthOctet; fourthOctet <= endFourthOctet; fourthOctet++)
        {
            currentOctet[3] = fourthOctet;
            std::ostringstream ss;
            ss << currentOctet[0] << "." << currentOctet[1] << "." << currentOctet[2] << "." << currentOctet[3];
            std::string ipAddress = ss.str();
            std::clog << "Scanning : " + ipAddress << std::endl;
            scanIp(ipAddress);
        }
    }
}
