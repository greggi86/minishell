cmake_minimum_required(VERSION 3.0.0)

project(minishell)

add_executable(env_ops env_ops.c)
add_executable(get_envp get_envp.c)
add_executable(m_builtins m_builtins.c)
add_executable(m_cd m_cd.c)
add_executable(m_echo m_echo.c)
add_executable(m_env m_env.c)
add_executable(m_exit m_exit.c)
add_executable(m_export m_export.c)
add_executable(m_unset m_unset.c)
add_executable(pwd pwd.c)
