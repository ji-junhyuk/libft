#include <stdarg.h>
#include <unistd.h>

# include <stdio.h>
int	find_len(int num);
int	ft_putnbr_fd(int n, int fd, int *printed);
int	print_sm_hex(va_list *ap, int *printed);
int	print_bg_hex(va_list *ap, int *printed);
int	print_per(va_list *ap, int *printed);
int	print_dec(va_list *ap, int *printed);
int	print_un_dec(va_list *ap, int *printed);
int	print_addr(void *ptr, int *printed);
int	print_ptr(va_list *ap, int *printed);
int 	ft_putstr(unsigned char *str, int *printed);
int	print_str(va_list *ap, int *printed);
int	print_char(va_list *ap, int *printed);
void	init_funcs(void *funcs[]);
int ft_printf(const char *format, ...);
//
//#include <stdio.h>
//#include <unistd.h>
//#include <stdlib.h>
//#include <string.h>
//
//int main(void)
//{
//	int num;
//	num = 210;
////	printf("%d\n",	ft_printf("junto%d\n", 123));
////	ft_printf("%d\n",	ft_printf("junto%d\n", 123));
//	printf("%u\n",	ft_printf("junto%u\n", 2147483649));
//	printf("%u\n",	ft_printf("junto%u\n", 2147483649));
//	printf("p:%p\n", &num);
//	ft_printf("ft_printf]:%p\n", &num);
//	printf("%x\n", num);
//	ft_printf("%x\n", num);
//	printf("%X\n", num);
//	ft_printf("%X\n", num);
////	ft_printf("junto%i\n", 123);
////	ft_printf("junto%%\n", 123);
//}
