ps -ef | grep './Sender.out' | grep -v grep | awk '{print $2}' | xargs -r kill -9