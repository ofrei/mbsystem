/*--------------------------------------------------------------------
 *    The MB-system:	mb_defaults.c	10/7/94
 *    $Id: mb_defaults.c 2261 2016-01-07 01:49:22Z caress $
 *
 *    Copyright (c) 1993-2016 by
 *    David W. Caress (caress@mbari.org)
 *      Monterey Bay Aquarium Research Institute
 *      Moss Landing, CA 95039
 *    and Dale N. Chayes (dale@ldeo.columbia.edu)
 *      Lamont-Doherty Earth Observatory
 *      Palisades, NY 10964
 *
 *    See README file for copying and redistribution conditions.
 *--------------------------------------------------------------------*/
/*
 * mb_defaults.c contains two functions - mb_defaults() and mb_env().
 * mb_defaults() returns the default MBIO control parameters and
 * mb_env() returns the default MB-System environment variables - all
 * values are read from ~/.mbio_defaults providing this file exists.
 * The return values are MB_SUCCESS if the file exists and MB_FAILURE
 * if it does not exist.
 *
 * Author:	D. W. Caress
 * Date:	January 23, 1993
 *
 *
 */

/* standard include files */
#include <stdio.h>
#include <math.h>
#include <string.h>

/* mbio include files */
#include "mb_status.h"
#include "mb_define.h"

static char rcs_id[]="$Id: mb_defaults.c 2261 2016-01-07 01:49:22Z caress $";

/*--------------------------------------------------------------------*/
int mb_defaults(int verbose, int *format, int *pings,
		int *lonflip, double bounds[4],
		int *btime_i, int *etime_i,
		double *speedmin, double *timegap)
{
	char	*function_name = "mb_defaults";
	int	status;
	FILE	*fp;
	char	file[MB_PATH_MAXLINE];
	char	string[MB_PATH_MAXLINE];
	char	*HOME = "HOME";
	char	*home_ptr;
	char	*getenv();

	/* print input debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> called\n",function_name);
		fprintf(stderr,"dbg2  Revision id: %s\n",rcs_id);
		fprintf(stderr,"dbg2  Input arguments:\n");
		fprintf(stderr,"dbg2       verbose: %d\n",verbose);
		}

	/* successful no matter what happens */
	status = MB_SUCCESS;

	/* set system default values */
	*format = 0;
	*pings = 1;
	*lonflip = 0;
	bounds[0] = -360.;
	bounds[1] = 360.;
	bounds[2] = -90.;
	bounds[3] = 90.;
	btime_i[0] = 1962;
	btime_i[1] = 2;
	btime_i[2] = 21;
	btime_i[3] = 10;
	btime_i[4] = 30;
	btime_i[5] = 0;
	btime_i[6] = 0;
	etime_i[0] = 2062;
	etime_i[1] = 2;
	etime_i[2] = 21;
	etime_i[3] = 10;
	etime_i[4] = 30;
	etime_i[5] = 0;
	etime_i[6] = 0;
	*speedmin = 0.0;
	*timegap = 1.0;

	/* set the filename */
	if ((home_ptr = getenv(HOME)) != NULL)
		{
		strcpy(file,home_ptr);
		strcat(file,"/.mbio_defaults");

		/* open and read values from file if possible */
		if ((fp = fopen(file, "r")) != NULL)
			{
			while (fgets(string,sizeof(string),fp) != NULL)
				{
				if (strncmp(string,"lonflip:",8) == 0)
					sscanf(string,"lonflip: %d",lonflip);
				if (strncmp(string,"speed:",6) == 0)
					sscanf(string,"timegap: %lf",timegap);
				}
 			fclose(fp);
			}
		}

	/* print output debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> completed\n",function_name);
		fprintf(stderr,"dbg2  Revision id: %s\n",rcs_id);
		fprintf(stderr,"dbg2  Return values:\n");
		fprintf(stderr,"dbg2       format:     %d\n",*format);
		fprintf(stderr,"dbg2       pings:      %d\n",*pings);
		fprintf(stderr,"dbg2       lonflip:    %d\n",*lonflip);
		fprintf(stderr,"dbg2       bounds[0]:  %f\n",bounds[0]);
		fprintf(stderr,"dbg2       bounds[1]:  %f\n",bounds[1]);
		fprintf(stderr,"dbg2       bounds[2]:  %f\n",bounds[2]);
		fprintf(stderr,"dbg2       bounds[3]:  %f\n",bounds[3]);
		fprintf(stderr,"dbg2       btime_i[0]: %d\n",btime_i[0]);
		fprintf(stderr,"dbg2       btime_i[1]: %d\n",btime_i[1]);
		fprintf(stderr,"dbg2       btime_i[2]: %d\n",btime_i[2]);
		fprintf(stderr,"dbg2       btime_i[3]: %d\n",btime_i[3]);
		fprintf(stderr,"dbg2       btime_i[4]: %d\n",btime_i[4]);
		fprintf(stderr,"dbg2       btime_i[5]: %d\n",btime_i[5]);
		fprintf(stderr,"dbg2       btime_i[6]: %d\n",btime_i[6]);
		fprintf(stderr,"dbg2       etime_i[0]: %d\n",etime_i[0]);
		fprintf(stderr,"dbg2       etime_i[1]: %d\n",etime_i[1]);
		fprintf(stderr,"dbg2       etime_i[2]: %d\n",etime_i[2]);
		fprintf(stderr,"dbg2       etime_i[3]: %d\n",etime_i[3]);
		fprintf(stderr,"dbg2       etime_i[4]: %d\n",etime_i[4]);
		fprintf(stderr,"dbg2       etime_i[5]: %d\n",etime_i[5]);
		fprintf(stderr,"dbg2       etime_i[6]: %d\n",etime_i[6]);
		fprintf(stderr,"dbg2       speedmin:   %f\n",*speedmin);
		fprintf(stderr,"dbg2       timegap:    %f\n",*timegap);
		fprintf(stderr,"dbg2  Return status:\n");
		fprintf(stderr,"dbg2       status:  %d\n",status);
		}

	/* return status */
	return(status);
}
/*--------------------------------------------------------------------*/
int mb_env(int verbose, char *psdisplay, char *imgdisplay, char *mbproject)
{
	char	*function_name = "mbenv";
	int	status;
	FILE	*fp;
	char	file[MB_PATH_MAXLINE];
	char	string[MB_PATH_MAXLINE];
	char	*HOME = "HOME";
	char	*home_ptr;
	char	*getenv();

	/* print input debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> called\n",function_name);
		fprintf(stderr,"dbg2  Revision id: %s\n",rcs_id);
		fprintf(stderr,"dbg2  Input arguments:\n");
		fprintf(stderr,"dbg2       verbose: %d\n",verbose);
		}

	/* set system default Postscript displayer */
#ifdef IRIX
	strcpy(psdisplay, "xpsview");
	strcpy(imgdisplay, "xv");
#endif
#ifdef IRIX64
	strcpy(psdisplay, "xpsview");
	strcpy(imgdisplay, "xv");
#endif
#ifdef SOLARIS
	strcpy(psdisplay, "pageview");
	strcpy(imgdisplay, "xv");
#endif
#ifdef LYNX
	strcpy(psdisplay, "gv");
	strcpy(imgdisplay, "xv");
#endif
#ifdef LINUX
	strcpy(psdisplay, "gv");
	strcpy(imgdisplay, "gimp");
#endif
#ifdef SUN
	strcpy(psdisplay, "pageview");
	strcpy(imgdisplay, "xv");
#endif
#ifdef HPUX
	strcpy(psdisplay, "gv");
	strcpy(imgdisplay, "xv");
#endif
#ifdef DARWIN
	strcpy(psdisplay, "gv");
	strcpy(imgdisplay, "display");
#endif
#ifdef CYGWIN
	strcpy(psdisplay, "gv");
	strcpy(imgdisplay, "xv");
#endif
#ifdef OTHER
	strcpy(psdisplay, "gv");
	strcpy(imgdisplay, "xv");
#endif

	/* successful no matter what happens */
	status = MB_SUCCESS;

	/* set system default project name */
	strcpy(mbproject, "none");

	/* set the filename */
	if ((home_ptr = getenv(HOME)) != NULL)
		{
		strcpy(file,home_ptr);
		strcat(file,"/.mbio_defaults");

		/* open and read values from file if possible */
		if ((fp = fopen(file, "r")) != NULL)
			{
			status = MB_SUCCESS;
			while (fgets(string,sizeof(string),fp) != NULL)
				{
				if (strncmp(string,"ps viewer:",10) == 0)
					sscanf(string,"ps viewer: %s",psdisplay);
				if (strncmp(string,"img viewer:",10) == 0)
					sscanf(string,"img viewer: %s",imgdisplay);
				if (strncmp(string,"project:",8) == 0)
					sscanf(string,"project: %s",mbproject);
				}
 			fclose(fp);
			}
		}

	/* print output debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> completed\n",function_name);
		fprintf(stderr,"dbg2  Revision id: %s\n",rcs_id);
		fprintf(stderr,"dbg2  Return values:\n");
		fprintf(stderr,"dbg2       psdisplay:  %s\n",psdisplay);
		fprintf(stderr,"dbg2       mbproject:  %s\n",mbproject);
		fprintf(stderr,"dbg2  Return status:\n");
		fprintf(stderr,"dbg2       status:  %d\n",status);
		}

	/* return status */
	return(status);
}
/*--------------------------------------------------------------------*/
int mb_lonflip(int verbose, int *lonflip)
{
	char	*function_name = "mb_lonflip";
	int	status;
	FILE	*fp;
	char	file[MB_PATH_MAXLINE];
	char	string[MB_PATH_MAXLINE];
	char	*HOME = "HOME";
	char	*home_ptr;
	char	*getenv();

	/* print input debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> called\n",function_name);
		fprintf(stderr,"dbg2  Revision id: %s\n",rcs_id);
		fprintf(stderr,"dbg2  Input arguments:\n");
		fprintf(stderr,"dbg2       verbose: %d\n",verbose);
		}

	/* successful no matter what happens */
	status = MB_SUCCESS;

	/* set system default values */
	*lonflip = 0;

	/* set the filename */
	if ((home_ptr = getenv(HOME)) != NULL)
		{
		strcpy(file,home_ptr);
		strcat(file,"/.mbio_defaults");

		/* open and read values from file if possible */
		if ((fp = fopen(file, "r")) != NULL)
			{
			while (fgets(string,sizeof(string),fp) != NULL)
				{
				if (strncmp(string,"lonflip:",8) == 0)
					sscanf(string,"lonflip: %d",lonflip);
				}
 			fclose(fp);
			}
		}

	/* print output debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> completed\n",function_name);
		fprintf(stderr,"dbg2  Revision id: %s\n",rcs_id);
		fprintf(stderr,"dbg2  Return values:\n");
		fprintf(stderr,"dbg2       lonflip:    %d\n",*lonflip);
		fprintf(stderr,"dbg2  Return status:\n");
		fprintf(stderr,"dbg2       status:  %d\n",status);
		}

	/* return status */
	return(status);
}
/*--------------------------------------------------------------------*/
int mb_mbview_defaults(int verbose,
			int *primary_colortable,
			int *primary_colortable_mode,
			int *primary_shade_mode,
			int *slope_colortable,
			int *slope_colortable_mode,
			int *secondary_colortable,
			int *secondary_colortable_mode,
			double *illuminate_magnitude,
			double *illuminate_elevation,
			double *illuminate_azimuth,
			double *slope_magnitude)
{
	char	*function_name = "mb_mbview_defaults";
	int	status;
	FILE	*fp;
	char	file[MB_PATH_MAXLINE];
	char	string[MB_PATH_MAXLINE];
	char	*HOME = "HOME";
	char	*home_ptr;
	char	*getenv();

	/* print input debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> called\n",function_name);
		fprintf(stderr,"dbg2  Revision id: %s\n",rcs_id);
		fprintf(stderr,"dbg2  Input arguments:\n");
		fprintf(stderr,"dbg2       verbose: %d\n",verbose);
		}

	/* successful no matter what happens */
	status = MB_SUCCESS;

	/* set system default values */
	*primary_colortable = 0;
	*primary_colortable_mode = 0;
	*primary_shade_mode = 2;
	*slope_colortable = 0;
	*slope_colortable_mode = 0;
	*secondary_colortable = 0;
	*secondary_colortable_mode = 1;
	*illuminate_magnitude = 2.0;
	*illuminate_elevation = 5.0;
	*illuminate_azimuth = 90.0;
	*slope_magnitude = 1.0;

	/* set the filename */
	if ((home_ptr = getenv(HOME)) != NULL)
		{
		strcpy(file,home_ptr);
		strcat(file,"/.mbio_defaults");

		/* open and read values from file if possible */
		if ((fp = fopen(file, "r")) != NULL)
			{
			while (fgets(string,sizeof(string),fp) != NULL)
				{
				if (strncmp(string,"mbview_primary_colortable:",25) == 0)
					sscanf(string,"mbview_primary_colortable:%d", primary_colortable);
				if (strncmp(string,"mbview_primary_colortable_mode:",30) == 0)
					sscanf(string,"mbview_primary_colortable_mode:%d", primary_colortable_mode);
				if (strncmp(string,"mbview_primary_shade_mode:",25) == 0)
					sscanf(string,"mbview_primary_shade_mode:%d", primary_shade_mode);
				if (strncmp(string,"mbview_slope_colortable:",23) == 0)
					sscanf(string,"mbview_slope_colortable:%d", slope_colortable);
				if (strncmp(string,"mbview_slope_colortable_mode:",28) == 0)
					sscanf(string,"mbview_slope_colortable_mode:%d", slope_colortable_mode);
				if (strncmp(string,"mbview_secondary_colortable:",27) == 0)
					sscanf(string,"mbview_secondary_colortable:%d", secondary_colortable);
				if (strncmp(string,"mbview_secondary_colortable_mode:",32) == 0)
					sscanf(string,"mbview_secondary_colortable_mode:%d", secondary_colortable_mode);
				if (strncmp(string,"mbview_illuminate_magnitude:",27) == 0)
					sscanf(string,"mbview_illuminate_magnitude:%lf", illuminate_magnitude);
				if (strncmp(string,"mbview_illuminate_elevation:",27) == 0)
					sscanf(string,"mbview_illuminate_elevation:%lf", illuminate_elevation);
				if (strncmp(string,"mbview_illuminate_azimuth:",25) == 0)
					sscanf(string,"mbview_illuminate_azimuth:%lf", illuminate_azimuth);
				if (strncmp(string,"mbview_slope_magnitude:",22) == 0)
					sscanf(string,"mbview_slope_magnitude:%lf", slope_magnitude);
				}
 			fclose(fp);
			}
		}

	/* print output debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> completed\n",function_name);
		fprintf(stderr,"dbg2  Revision id: %s\n",rcs_id);
		fprintf(stderr,"dbg2  Return values:\n");
		fprintf(stderr,"dbg2       primary_colortable:         %d\n",*primary_colortable);
		fprintf(stderr,"dbg2       primary_colortable_mode:    %d\n",*primary_colortable_mode);
		fprintf(stderr,"dbg2       primary_shade_mode:         %d\n",*primary_shade_mode);
		fprintf(stderr,"dbg2       slope_colortable:           %d\n",*slope_colortable);
		fprintf(stderr,"dbg2       slope_colortable_mode:      %d\n",*slope_colortable_mode);
		fprintf(stderr,"dbg2       secondary_colortable:       %d\n",*secondary_colortable);
		fprintf(stderr,"dbg2       secondary_colortable_mode:  %d\n",*secondary_colortable_mode);
		fprintf(stderr,"dbg2       illuminate_magnitude:       %f\n",*illuminate_magnitude);
		fprintf(stderr,"dbg2       illuminate_elevation:       %f\n",*illuminate_elevation);
		fprintf(stderr,"dbg2       illuminate_azimuth:         %f\n",*illuminate_azimuth);
		fprintf(stderr,"dbg2       slope_magnitude:            %f\n",*slope_magnitude);
		fprintf(stderr,"dbg2  Return status:\n");
		fprintf(stderr,"dbg2       status:  %d\n",status);
		}

	/* return status */
	return(status);
}
/*--------------------------------------------------------------------*/
int mb_fbtversion(int verbose, int *fbtversion)
{
	char	*function_name = "mb_fbtversion";
	int	status;
	FILE	*fp;
	char	file[MB_PATH_MAXLINE];
	char	string[MB_PATH_MAXLINE];
	char	*HOME = "HOME";
	char	*home_ptr;
	char	*getenv();

	/* print input debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> called\n",function_name);
		fprintf(stderr,"dbg2  Revision id: %s\n",rcs_id);
		fprintf(stderr,"dbg2  Input arguments:\n");
		fprintf(stderr,"dbg2       verbose: %d\n",verbose);
		}

	/* successful no matter what happens */
	status = MB_SUCCESS;

	/* set system default values */
	*fbtversion = 3;

	/* set the filename */
	if ((home_ptr = getenv(HOME)) != NULL)
		{
		strcpy(file,home_ptr);
		strcat(file,"/.mbio_defaults");

		/* open and read values from file if possible */
		if ((fp = fopen(file, "r")) != NULL)
			{
			while (fgets(string,sizeof(string),fp) != NULL)
				{
				if (strncmp(string,"fbtversion:",11) == 0)
					sscanf(string,"fbtversion: %d",fbtversion);
				}
 			fclose(fp);
			}
		}

	/* print output debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> completed\n",function_name);
		fprintf(stderr,"dbg2  Revision id:     %s\n",rcs_id);
		fprintf(stderr,"dbg2  Return values:\n");
		fprintf(stderr,"dbg2       fbtversion: %d\n",*fbtversion);
		fprintf(stderr,"dbg2  Return status:\n");
		fprintf(stderr,"dbg2       status:     %d\n",status);
		}

	/* return status */
	return(status);
}
/*--------------------------------------------------------------------*/
int mb_uselockfiles(int verbose, int *uselockfiles)
{
	char	*function_name = "mb_uselockfiles";
	int	status;
	FILE	*fp;
	char	file[MB_PATH_MAXLINE];
	char	string[MB_PATH_MAXLINE];
	char	*HOME = "HOME";
	char	*home_ptr;
	char	*getenv();

	/* print input debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> called\n",function_name);
		fprintf(stderr,"dbg2  Revision id: %s\n",rcs_id);
		fprintf(stderr,"dbg2  Input arguments:\n");
		fprintf(stderr,"dbg2       verbose: %d\n",verbose);
		}

	/* successful no matter what happens */
	status = MB_SUCCESS;

#ifdef WIN32
	/* It would crash because the lock file is attempted to be created with the new "wx"
	   that VC12 does not know and we don't have any use for this anyway.
	*/
	*uselockfiles = 0;
	return(status);
#endif

	/* set system default values */
	*uselockfiles = 1;

	/* set the filename */
	if ((home_ptr = getenv(HOME)) != NULL)
		{
		strcpy(file,home_ptr);
		strcat(file,"/.mbio_defaults");

		/* open and read values from file if possible */
		if ((fp = fopen(file, "r")) != NULL)
			{
			while (fgets(string,sizeof(string),fp) != NULL)
				{
				if (strncmp(string,"uselockfiles:",13) == 0)
					sscanf(string,"uselockfiles:%d",uselockfiles);
				if (*uselockfiles < 0 || *uselockfiles > 1)
					*uselockfiles = 1;
				}
 			fclose(fp);
			}
		}

	/* print output debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> completed\n",function_name);
		fprintf(stderr,"dbg2  Revision id:       %s\n",rcs_id);
		fprintf(stderr,"dbg2  Return values:\n");
		fprintf(stderr,"dbg2       uselockfiles: %d\n",*uselockfiles);
		fprintf(stderr,"dbg2  Return status:\n");
		fprintf(stderr,"dbg2       status:       %d\n",status);
		}

	/* return status */
	return(status);
}
/*--------------------------------------------------------------------*/
int mb_fileiobuffer(int verbose, int *fileiobuffer)
{
	char	*function_name = "mb_fileiobuffer";
	int	status;
	FILE	*fp;
	char	file[MB_PATH_MAXLINE];
	char	string[MB_PATH_MAXLINE];
	char	*HOME = "HOME";
	char	*home_ptr;
	char	*getenv();

	/* print input debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> called\n",function_name);
		fprintf(stderr,"dbg2  Revision id: %s\n",rcs_id);
		fprintf(stderr,"dbg2  Input arguments:\n");
		fprintf(stderr,"dbg2       verbose: %d\n",verbose);
		}

	/* successful no matter what happens */
	status = MB_SUCCESS;

	/* set system default values */
	*fileiobuffer = 0;

	/* set the filename */
	if ((home_ptr = getenv(HOME)) != NULL)
		{
		strcpy(file,home_ptr);
		strcat(file,"/.mbio_defaults");

		/* open and read values from file if possible */
		if ((fp = fopen(file, "r")) != NULL)
			{
			while (fgets(string,sizeof(string),fp) != NULL)
				{
				if (strncmp(string,"fileiobuffer:",13) == 0)
					sscanf(string,"fileiobuffer:%d",fileiobuffer);
				}
 			fclose(fp);
			}
		}

	/* print output debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> completed\n",function_name);
		fprintf(stderr,"dbg2  Revision id:       %s\n",rcs_id);
		fprintf(stderr,"dbg2  Return values:\n");
		fprintf(stderr,"dbg2       fileiobuffer: %d\n",*fileiobuffer);
		fprintf(stderr,"dbg2  Return status:\n");
		fprintf(stderr,"dbg2       status:       %d\n",status);
		}

	/* return status */
	return(status);
}
/*--------------------------------------------------------------------*/
