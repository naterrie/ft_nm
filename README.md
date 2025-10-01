# ft_nm
Project ft_nm of 42.
nm is a UNIX function that examin binary files.
In this project we have to write a program in C who does the same things (with bonus flags).
For this project we use ELF Format (struct and DEFINE) with a map.

## How nm work

nm is a function that list the symbols from objects file, if there isnt any arguments he will take a.out
He show each symbol in a different link with somes informations :
value type name

Value is the hexadicemal value of the symbol

Type is the type of the symbol who will depend on the type, bind and flags (most of the lowercase arer local except u v and w)

Name is the name of the symbol, if it has a version information associated it will displayed if there isnt the version string is displayed

### Header

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

- `e_ident` is the magics number (the 4 first must be in order : 0x7f, E, L and F), next are other informations, like 32 or 64 bits, version...
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

We start to cast the man in this struct, with this you can check some classic information, if it's an ELF, 32bits or 64bits, if the offset is not highter than the size and other to be sure that the arguments isn't corrupted or invalid.
Then we can cast the map in Shdr using the e_shoff

### Section struct

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
- `sh_name` is the section name
- `sh_type` is the section type
- `sh_flags` is the section flags
- `sh_addr` is the section virtual addr at execution
- `sh_offset` is the section file offset
- `sh_size` is the section size in bytes
- `sh_link` is the section link to an other section
- `sh_info` is the section information whose depend on section type
- `sh_addralign` is the section alignement constraints
- `sh_entsize` if the section hold a table it's the entry size

(for more information about ELF Section click [here](https://docs.oracle.com/cd/E19683-01/816-1386/chapter6-94076/index.html))

Now with the section header struct we can check if .symtab and .strtab exist and their position to cast it in the symbol struct

### Symbol struct

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
- `st_info` is the symbol type and attributes
- `st_other` is the symbol visibility
- `st_shndx` is the symbol entry defined by the section
- `st_value` is the symbol value
- `st_size` is the symbol size

(For more information about sym, click [here](https://docs.oracle.com/cd/E19683-01/816-1386/6m7qcoblj/index.html#chapter6-79797))

nm use this struct to show the symbols information, name, type and value if possible
*Listing every symbol type will take too much space and time, prefer reading the [man](https://man7.org/linux/man-pages/man1/nm.1.html)*

Some symbols may not have a name, those will be listed if the flag '-a' is activated
For the type it will depend of a lot of variable, if it's weak, global, where in the code (text, date...)
The value is like the name, instead it's the undefined symbol who will not have a value

It display it like this : value type name

## The sorts
nm have a strange but logical sort :
Alphabetical order, skip _ char and a A are the same
Reverse (-r) will reverse the sort
And last for this project, the no sort (-p) will directly show the output without any sort before

In any case if two symbol have the same name it will compare the value, the one with the lowest value will be print first

## Explanation of the program

First, the programme check the number of args, if there is a flag, if there is only one nm take a.out automatically
If the file exist we check start the firts check, ELF, offset and size comparaison and others
Then we cast the map, use the offset of Ehdr and Shdr to get the position of the symbols.
Here we save the symbols, (those without name when a isnt active arent saved).
For each symbol we try to get the good type depending of the bind and type idx all of those informations are avaible using a define from the elf header except for the type N who i found be the only needed the section name.

## Bonus

The bonus of the project are the flags : a, p, u, g and r
r reverse sort the list
p doesnt sort the list
a add the debug file (found in symtab)
u show the undefined only
g show the extern only

Flags have an priority order depending of if it's a sort flag or a show symbols, the others are automatically disabled.
For the sort on this project we only have p and r, if both are used it will be p who will always be used
And for the symbols we have u a ang g, the priority is the same as written
