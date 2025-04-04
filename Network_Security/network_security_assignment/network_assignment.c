#include <pcap.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <net/ethernet.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void packet_handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
    struct ether_header *eth = (struct ether_header *)packet;

    if (ntohs(eth->ether_type) != 0x0800) return;

    struct ip *ip_hdr = (struct ip *)(packet + 14);
    int ip_header_len = ip_hdr->ip_hl * 4;

    if (ip_hdr->ip_p != IPPROTO_TCP) return;

    struct tcphdr *tcp_hdr = (struct tcphdr *)(packet + 14 + ip_header_len);
    int tcp_header_len = tcp_hdr->th_off * 4;

    printf("Ethernet: %02x:%02x:%02x:%02x:%02x:%02x -> %02x:%02x:%02x:%02x:%02x:%02x\n",
            eth->ether_shost[0], eth->ether_shost[1], eth->ether_shost[2],
            eth->ether_shost[3], eth->ether_shost[4], eth->ether_shost[5],
            eth->ether_dhost[0],eth->ether_dhost[1], eth->ether_dhost[2],
            eth->ether_dhost[3], eth->ether_dhost[4], eth->ether_dhost[5]        
    );
    printf("IP: %s -> %s\n", inet_ntoa(ip_hdr->ip_src), inet_ntoa(ip_hdr->ip_dst));
    printf("TCP: %d -> %d\n", ntohs(tcp_hdr->th_sport), ntohs(tcp_hdr->th_dport));

    const u_char *payload = packet + 14 + ip_header_len + tcp_header_len;
    int payload_len = header->caplen - (14 + ip_header_len + tcp_header_len);

    if(payload_len > 0) {
        printf("Message: ");
        for(int i = 0; i < payload_len && i < 20; i++) {
            printf("%c", isprint(payload[i]) ? payload[i] : '.');
        }
        printf("\n");
    }
    printf("==================================\n");
}

int main() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_live("eth0", BUFSIZ, 1, 1000, errbuf);

    if (handle == 0) {
        fprintf(stderr, "Could not open device: %s\n", errbuf);
        return 2;
    }

    pcap_loop(handle, 0, packet_handler, 0);
    pcap_close(handle);

    return 0;
}