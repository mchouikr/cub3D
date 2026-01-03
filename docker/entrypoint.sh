#!/bin/sh

status=0
if [ "$#" -eq 0 ]; then
	/bin/bash
	status=$?
else
	"$@"
	status=$?
fi

auto_fclean="${CUB3D_AUTO_FCLEAN:-${MSH_AUTO_FCLEAN:-1}}"
if [ "$auto_fclean" != "0" ] && [ -f /workspace/Makefile ]; then
	(cd /workspace && make fclean) || true
fi

exit $status
