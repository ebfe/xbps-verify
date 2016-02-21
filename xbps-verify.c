#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <xbps.h>

static char* signed_by = NULL;

static void die(char *msg, int err) {
	fprintf(stderr, "xbps-verify: %s: %s\n", msg, strerror(err));
	exit(1);
}

static int verify_pkg_file(struct xbps_repo *repo, void *file, bool *done) {
	if (!repo->is_signed) {
		return 0;
	}
	if (xbps_verify_file_signature(repo, file)) {
		signed_by = strdup(repo->uri);
		*done = true;
	}
	return 0;
}

int main(int argc, char *argv[]) {
	struct xbps_handle xhp = {0};
	int err;

	err = xbps_init(&xhp);
	if (err) {
		die("xbps_init", err);
	}

	err = xbps_rpool_foreach(&xhp, verify_pkg_file, argv[1]);
	if (err) {
		die("xbps_rpool_foreach", err);
	}

	if (signed_by != NULL) {
		printf("good signature from '%s'\n", signed_by);
		return 0;
	}

	xbps_end(&xhp);
	return 1;
}
