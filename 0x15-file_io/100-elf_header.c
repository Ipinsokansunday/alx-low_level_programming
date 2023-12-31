#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void checkElf(unsigned char *e_ident);
void printMagic(unsigned char *e_ident);
void printClass(unsigned char *e_ident);
void printData(unsigned char *e_ident);
void printVersion(unsigned char *e_ident);
void printOsAbi(unsigned char *e_ident);
void printAbi(unsigned char *e_ident);
void printType(unsigned int e_type, unsigned char *e_ident);
void printEntry(unsigned long int e_entry, unsigned char *e_ident);
void closeElf(int elf);

void checkElf(unsigned char *e_ident)
{
	for (int index = 0; index < 4; index++)
	{
		if (e_ident[index] != 127 && e_ident[index] != 'E' && e_ident[index] != 'L' && e_ident[index] != 'F')
		{
			dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
			exit(98);
		}
	}
}

/**
 * check_elf - Checks if a file is an ELF file based on its magic numbers.
 * @e_ident: A pointer to an array containing the ELF magic numbers.
 *
 * If the file is not an ELF file, the function exits with exit code 98.
 */

void printMagic(unsigned char *e_ident)
{
	printf("  Magic:   ");
	for (int index = 0; index < EI_NIDENT; index++)
	{
		printf("%02x", e_ident[index]);
		if (index == EI_NIDENT - 1)
		printf("\n");
		else
		printf(" ");
	}
}

/**
 * printMagic - Print the magic numbers in the ELF header.
 * @e_ident: A pointer to an array containing the ELF magic numbers.
 *
 * This function prints the magic numbers of the ELF header, which are
 * represented as hexadecimal values separated by spaces.
 */

void printClass(unsigned char *e_ident)
{
	printf("  Class:                             ");
	switch (e_ident[EI_CLASS])
	{
		case ELFCLASSNONE:
		printf("none\n");
		break;
		case ELFCLASS32:
		printf("ELF32\n");
		break;
		case ELFCLASS64:
		printf("ELF64\n");
		break;
		default:
		printf("<unknown: %x>\n", e_ident[EI_CLASS]);
	}
}

/**
 * printClass - Prints the class of an ELF header.
 * @e_ident: A pointer to an array containing the ELF class.
 */

void printData(unsigned char *e_ident)
{
	printf("  Data:                              ");
	switch (e_ident[EI_DATA])
	{
		case ELFDATANONE:
		printf("none\n");
		break;
		case ELFDATA2LSB:
		printf("2's complement, little endian\n");
		break;
		case ELFDATA2MSB:
		printf("2's complement, big endian\n");
		break;
		default:
		printf("<unknown: %x>\n", e_ident[EI_CLASS]);
	}
}

/**
 * print_data - Prints the data encoding of an ELF header.
 * @e_ident: A pointer to an array containing
 * the ELF identification bytes.
 *
 * This function interprets the data encoding
 * (endianness) information from the
 * ELF identification bytes and prints it in
 * a human-readable format.
 */
void printVersion(unsigned char *e_ident)
{
	printf("  Version:                           %d", e_ident[EI_VERSION]);
	switch (e_ident[EI_VERSION])
	{
		case EV_CURRENT:
		printf(" (current)\n");
		break;
		default:
		printf("\n");
		break;
	}
}
/**
 * print_version - Prints the ELF version of an ELF header.
 * @e_ident: A pointer to an array containing the ELF version.
 */

void printOsAbi(unsigned char *e_ident)
{
	printf("  OS/ABI:                            ");
	switch (e_ident[EI_OSABI])
	{
		case ELFOSABI_NONE:
		printf("UNIX - System V\n");
		break;
		case ELFOSABI_HPUX:
		printf("UNIX - HP-UX\n");
		break;
		case ELFOSABI_NETBSD:
		printf("UNIX - NetBSD\n");
		break;
		case ELFOSABI_LINUX:
		printf("UNIX - Linux\n");
		break;
		case ELFOSABI_SOLARIS:
		printf("UNIX - Solaris\n");
		break;
		case ELFOSABI_IRIX:
		printf("UNIX - IRIX\n");
		break;
		case ELFOSABI_FREEBSD:
		printf("UNIX - FreeBSD\n");
		break;
		case ELFOSABI_TRU64:
		printf("UNIX - TRU64\n");
		break;
		case ELFOSABI_ARM:
		printf("ARM\n");
		break;
		case ELFOSABI_STANDALONE:
		printf("Standalone App\n");
		break;
		default:
		printf("<unknown: %x>\n", e_ident[EI_OSABI]);
	}
}



/**
 * printAbi - Prints the ABI version of an ELF header.
 * @e_ident: A pointer to an array containing the ELF ABI version.
 */

void printAbi(unsigned char *e_ident)
{
	printf("  ABI Version:                       %d\n", e_ident[EI_ABIVERSION]);
}

/**
 * printType - Prints the type of an ELF header.
 * @e_type: The ELF type.
 * @e_ident: A pointer to an array containing the ELF class.
 */

void printType(unsigned int e_type, unsigned char *e_ident)
{
	if (e_ident[EI_DATA] == ELFDATA2MSB)
	e_type >>= 8;

	printf("  Type:                              ");
	switch (e_type)
	{
		case ET_NONE:
		printf("NONE (None)\n");
		break;
		case ET_REL:
		printf("REL (Relocatable file)\n");
		break;
		case ET_EXEC:
		printf("EXEC (Executable file)\n");
		break;
		case ET_DYN:
		printf("DYN (Shared object file)\n");
		break;
		case ET_CORE:
		printf("CORE (Core file)\n");
		break;
		default:
		printf("<unknown: %x>\n", e_type);
	}
}

/**
 * print_entry - Prints the entry point address of an ELF header.
 * @e_entry: The entry point address to be printed.
 * @e_ident: A pointer to an array containing the
 * ELF identification bytes.
 *
 * This function prints the entry point
 * address of an ELF header in a human-readable format.
 */
void printEntry(unsigned long int e_entry, unsigned char *e_ident)
{
	printf("  Entry point address:               ");
	if (e_ident[EI_DATA] == ELFDATA2MSB)
	{
		e_entry = ((e_entry << 8) & 0xFF00FF00) | ((e_entry >> 8) & 0xFF00FF);
		e_entry = (e_entry << 16) | (e_entry >> 16);
	}

	if (e_ident[EI_CLASS] == ELFCLASS32)
	printf("%#x\n", (unsigned int)e_entry);
	else
	printf("%#lx\n", e_entry);
}

/**
 * closeElf - Closes an ELF file.
 * @elf: The file descriptor of the ELF file.
 *
 * Description: If the file cannot be closed, it exits with exit code 98.
 */

void closeElf(int elf)
{
	if (close(elf) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", elf);
		exit(98);
	}
}

/**
 * main - Display the information from the ELF header of a given file.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line argument strings.
 *
 * Return: 0 on success, or exit code 98 on failure.
 */
int main(int argc, char *argv[])
{
	Elf64_Ehdr *header;
	int fd, result;

	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "Usage: %s <filename>\n", argv[0]);
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
		exit(98);
	}

	header = malloc(sizeof(Elf64_Ehdr));
	if (header == NULL)
	{
		closeElf(fd);
		dprintf(STDERR_FILENO, "Error: Memory allocation failed\n");
		exit(98);
	}
	result = read(fd, header, sizeof(Elf64_Ehdr);
	if (result == -1)
	{
		free(header);
		closeElf(fd);
		dprintf(STDERR_FILENO, "Error: Reading file failed\n");
		exit(98);
	}
	checkElf(header->e_ident);
	printf("ELF Header:\n");
	printMagic(header->e_ident);
	printClass(header->e_ident);
	printData(header->e_ident);
	printVersion(header->e_ident);
	printOsAb
}
