# ft_nm
Project ft_nm of 42.
nm is a UNIX function that examin binary files.
In this project we have to write a program in C who does the same things (with bonus flags).
For this project we use ELF Format (struct and DEFINE) with a map.

## Header struct
With the map we can cast it in the ELF struct Ehdr (64 or 32 bits) who is defined like this :

```c
#define EI_NIDENT 16
typedef struct
{
	unsigned char	e_ident[EI_NIDENT];
	uint16_t		e_type;
	uint16_t		e_machine;
	uint32_t		e_version;
	ElfN_Addr		e_entry;
	ElfN_Off		e_phoff;
	ElfN_Off		e_shoff;
	uint32_t		e_flags;
	uint16_t		e_ehsize;
	uint16_t		e_phentsize;
	uint16_t		e_phnum;
	uint16_t		e_shentsize;
	uint16_t		e_shnum;
	uint16_t		e_shstrndx;
} ElfN_Ehdr;
```

e_ident is the magics number (the 4 first must be in order : 0x7f, E, L and F), next are other informations, like 32 or 64 bits, version...
(for more information about ELF Identification click [here](https://docs.oracle.com/cd/E19683-01/816-1386/6m7qcoblj/index.html#chapter6-35342))

- `e_type` is the type of the file

- `e_machine` specifies the architecture of the file

- `e_version` identifies the object file (EV_NONE who is equal to 0 is invalid)

- `e_entry` is the value of the entry of the program adress (typical for a main), the value is 0 is there is not

- `e_phoff` is the program header table file offset in bytes

- `e_shoff` is the section header table file offset in bytes

- `e_flags` is the processor flags

- `e_ehsize` is the header size in bytes

- `e_phentsize` is the program header table entry size

- `e_phnum` is the program header table entry count

- `e_shentsize` is the section header table entry size

- `e_shnum` is the section header table entry count

- `e_shstrndx` is the section header string table index

(for more information about ELF Header click [here](https://docs.oracle.com/cd/E19683-01/816-1386/chapter6-43405/index.html))

## Section struct

Once we have the Ehdr struct, map can be cast in an other struct from ELF named Shdr (32 or 64 bits) who is defined like this :

```c
typedef struct
{
	Elf64_Word		sh_name;
	Elf64_Word		sh_type;
	Elf64_Xword		sh_flags;
	Elf64_Addr		sh_addr;
	Elf64_Off		sh_offset;
	Elf64_Xword		sh_size;
	Elf64_Word		sh_link;
	Elf64_Word		sh_info;
	Elf64_Xword		sh_addralign;
	Elf64_Xword		sh_entsize;
} Elf64_Shdr;
```
- `sh_name`
- `sh_type`
- `sh_flages`
- `sh_addr`
- `sh_offset`
- `sh_size`
- `sh_link`
- `sh_info`
- `sh_addralign`
- `sh_entsize`

## Symbol struct

```c
typedef struct
{
	Elf64_Word		st_name;
	unsigned char	st_info;
	unsigned char	st_other;
	Elf64_Half		st_shndx;
	Elf64_Addr		st_value;
	Elf64_Xword		st_size;
} Elf64_Sym;
```

- `st_name` is the symbol name
- `st_info` 
- `st_other`
- `st_shndx`
- `st_value` is the symbol value
- `st_size` is the symbol size

(for more information, click [here](https://docs.oracle.com/cd/E19683-01/816-1386/6m7qcoblj/index.html#chapter6-79797))
