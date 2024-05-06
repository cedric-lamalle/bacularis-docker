#!/bin/bash

POSTGRESQL_USER='postgres'
BACULA_DBNAME='bacula'
BACULA_DBUSER='bacula'
BACULA_DBPASSWORD='bacula'
BACULA_USER='bacula'

function start_postgresql()
{
	/etc/init.d/postgresql start
}

function stop_postgresql()
{
	/etc/init.d/postgresql stop
}

function init_bacula()
{
    su ${POSTGRESQL_USER} -c "db_name='${BACULA_DBNAME}' /opt/bacula/scripts/create_postgresql_database"
    su ${POSTGRESQL_USER} -c "db_name='${BACULA_DBNAME}' /opt/bacula/scripts/make_postgresql_tables"
    su ${POSTGRESQL_USER} -c "db_name='${BACULA_DBNAME}' db_user='${BACULA_DBUSER}'  db_password='${BACULA_DBPASSWORD}' /opt/bacula/scripts/grant_postgresql_privileges"
}

function start_bacula_dir()
{
    if ! su ${POSTGRESQL_USER} -c 'psql -l' | grep '^ bacula' 1>/dev/null
    then
        init_bacula
    fi

    /opt/bacula/scripts/bacula-director start
}

function stop_bacula_dir()
{
    /opt/bacula/scripts/bacula-director stop
}

function start_bacula_sd()
{
    /opt/bacula/scripts/bacula-sd start
}

function stop_bacula_sd()
{
    /opt/bacula/scripts/bacula-sd stop
}

function start_bacula_fd()
{
    /opt/bacula/scripts/bacula-fd start
}

function stop_bacula_fd()
{
    /opt/bacula/scripts/bacula-fd stop
}

function start_php_fpm()
{
    /etc/init.d/php8.2-fpm start
}

function stop_php_fpm()
{
    /etc/init.d/php8.2-fpm stop
}
