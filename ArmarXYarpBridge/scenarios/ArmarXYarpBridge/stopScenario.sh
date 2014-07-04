if test -z "$1"
then
    KILL_SIGNAL=2
else
    KILL_SIGNAL=$1
fi

skill ()
{
    EXECUTABLE_STR=`ps aux | grep "$1 \-\-Ice.Default" | grep -v grep | awk '{print $2}'`
    if [ ${#EXECUTABLE_STR} == 0 ]
    then
        echo skipping $1
    else
        echo killing $1
        kill -s $2 ${EXECUTABLE_STR}
    fi
}

echo SENDING ${KILL_SIGNAL} TO ALL PROCESSES

skill YarpKinematicUnitAppRun ${KILL_SIGNAL}

skill YarpImageProviderAppRun ${KILL_SIGNAL}

skill YarpHandUnitAppRun ${KILL_SIGNAL}

