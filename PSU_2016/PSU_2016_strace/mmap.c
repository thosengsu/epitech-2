/*
** mmap.c<src> for strace in /home/tom/Documents/TEK2/PSU_2016/PSU_2016_strace/src
**
** Made by MonsieurTom
** Login   <tom.lenormand@epitech.eu>
**
** Started on  Thu Apr 13 00:19:41 2017 MonsieurTom
** Last update Sun Apr 16 14:43:31 2017 Alexis Lavenu
*/

#include <sys/user.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "strace.h"

static t_flag		g_mmap_flags[] =
  {
    {MAP_SHARED, "MAP_SHARED"},
    {MAP_PRIVATE, "MAP_PRIVATE"},
    {MAP_32BIT, "MAP_32BIT"},
    {MAP_FIXED, "MAP_FIXED"},
    {MAP_ANONYMOUS, "MAP_ANONYMOUS"},
    {MAP_DENYWRITE, "MAP_DENYWRITE"},
    {MAP_GROWSDOWN, "MAP_GROWSDOWN"},
    {MAP_HUGETLB, "MAP_HUGETLB"},
    {MAP_LOCKED, "MAP_LOCKED"},
    {MAP_NONBLOCK, "MAP_NONBLOCK"},
    {MAP_NORESERVE, "MAP_NORESERVE"},
    {MAP_POPULATE, "MAP_POPULATE"},
    {MAP_STACK, "MAP_STACK"},
    {0, NULL}
  };

void			p_mmap_flags(long flag)
{
  bool			first;
  int			i;

  i = 0;
  first = true;
  if (g_s != true)
    {
      printf("0x%x", (unsigned int)flag);
      return ;
    }
  while (g_mmap_flags[i].flag_name != NULL)
    {
      if (g_mmap_flags[i].flag & flag)
	{
	  if (first == true)
	    printf("%s", g_mmap_flags[i].flag_name);
	  else
	    printf("|%s", g_mmap_flags[i].flag_name);
	  first = false;
	}
      i++;
    }
}

void			p_mmap_proto(long proto)
{
  bool			first;

  first = true;
  if (g_s != true)
    {
      printf("0x%x", (unsigned int)proto);
      return ;
    }
  if (proto)
    {
      if (proto & PROT_READ)
	{
	  printf("PROT READ");
	  first = false;
	}
      if (proto & PROT_WRITE)
	{
	  printf((first == true) ? ("PROTE_WRITE") : ("|PROT_WRITE"));
	  first = false;
	}
      if (proto & PROT_EXEC)
	printf((first == true) ? ("PROTE_EXEC") : ("|PROT_EXEC"));
    }
  else
    printf("PROT_NONE");
}

void			print_mmap2(pid_t child, struct user_regs_struct data,
				    long return_v)
{
  printf("mmap2(");
  p_void_p(child, find_reg(data, 0));
  printf(", ");
  p_size_t(child, find_reg(data, 1));
  printf(", ");
  p_mmap_proto(find_reg(data, 2));
  printf(", ");
  p_mmap_flags(find_reg(data, 3));
  printf(", ");
  p_int(child, find_reg(data, 4));
  printf(", ");
  p_off_t(child, find_reg(data, 5));
  printf(") = ");
  if (g_s == true)
    {
      if (return_v < 0)
	printf("-1 ENOENT (%s)", strerror(-return_v));
      else
	p_void_p(child, return_v);
    }
  else
    printf("0x%x", (unsigned int)return_v);
  printf("\n");
}

void			print_mmap(pid_t child, struct user_regs_struct data,
				   long return_v)
{
  printf("mmap(");
  p_void_p(child, find_reg(data, 0));
  printf(", ");
  p_size_t(child, find_reg(data, 1));
  printf(", ");
  p_mmap_proto(find_reg(data, 2));
  printf(", ");
  p_mmap_flags(find_reg(data, 3));
  printf(", ");
  p_int(child, find_reg(data, 4));
  printf(", ");
  p_off_t(child, find_reg(data, 5));
  printf(") = ");
  if (g_s == true)
    {
      if (return_v < 0)
	printf("-1 (%s)", strerror(-return_v));
      else
	p_void_p(child, return_v);
    }
  else
    printf("0x%x", (unsigned int)return_v);
  printf("\n");
}
