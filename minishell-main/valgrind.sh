#!/bin/bash

make cleanly && valgrind --leak-check=full ./minishell && make fclean