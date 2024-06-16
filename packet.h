/*
 * packet.h
 *
 *  Created on: Sep 15, 2017
 *      Author: root
 */

#ifndef PACKET_H_
#define PACKET_H_

#include "common.h"
#include "fd_manager.h"

extern int iv_min;
extern int iv_max;  //< 256;

extern u64_t packet_send_count;
extern u64_t dup_packet_send_count;
extern u64_t packet_recv_count;
extern u64_t dup_packet_recv_count;
#define BYTES_PER_XOR_CRYPT sizeof(uint64_t)
#define MINIMAL_KEY_LENGTH 32
#define MAXIMAL_KEY_LENGTH 1000 // including ending \0
extern char key_string[MAXIMAL_KEY_LENGTH*BYTES_PER_XOR_CRYPT];
extern int disable_replay_filter;
extern int random_drop;
extern int disable_obscure;
extern int disable_xor;

int my_send(const dest_t &dest, char *data, int len);

void initialize_key_string();
void xor_crypt(char *input, int &len);
int add_seq(char *data, int &data_len);
int remove_seq(char *data, int &data_len);
int do_obscure(const char *input, int in_len, char *output, int &out_len);
int de_obscure(const char *input, int in_len, char *output, int &out_len);

// int sendto_fd_u64 (int fd,u64_t u64,char * buf, int len,int flags);
int sendto_ip_port(u32_t ip, int port, char *buf, int len, int flags);
int send_fd(int fd, char *buf, int len, int flags);

int put_conv(u32_t conv, const char *input, int len_in, char *&output, int &len_out);
int get_conv(u32_t &conv, const char *input, int len_in, char *&output, int &len_out);
int put_crc32(char *s, int &len);
int rm_crc32(char *s, int &len);
int do_cook(char *data, int &len);
int de_cook(char *s, int &len);
#endif /* PACKET_H_ */
