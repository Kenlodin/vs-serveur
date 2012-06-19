while [ 1 ]
do
	git pull > tmp.log
	NB_LINE=`wc -l tmp.log`
	if [ NB_LINE = "1" ]
	then
		continue
	fi
	make
	sh loader.sh
	rm tmp.log
	sleep 900
done
