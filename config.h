/* See LICENSE file for copyright and license details. */

/* interval between updates (in ms) */
const unsigned int interval = 10000;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "";

/* maximum output string length */
#define MAXLEN 2048

/*
 * function            description                     argument (example)
 *
 * battery_perc        battery percentage              battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_remaining   battery remaining HH:MM         battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_state       battery charging state          battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * cat                 read arbitrary file             path
 * cpu_freq            cpu frequency in MHz            NULL
 * cpu_perc            cpu usage in percent            NULL
 * datetime            date and time                   format string (%F %T)
 * disk_free           free disk space in GB           mountpoint path (/)
 * disk_perc           disk usage in percent           mountpoint path (/)
 * disk_total          total disk space in GB          mountpoint path (/)
 * disk_used           used disk space in GB           mountpoint path (/)
 * entropy             available entropy               NULL
 * gid                 GID of current user             NULL
 * hostname            hostname                        NULL
 * ipv4                IPv4 address                    interface name (eth0)
 * ipv6                IPv6 address                    interface name (eth0)
 * kernel_release      `uname -r`                      NULL
 * keyboard_indicators caps/num lock indicators        format string (c?n?)
 *                                                     see keyboard_indicators.c
 * keymap              layout (variant) of current     NULL
 *                     keymap
 * load_avg            load average                    NULL
 * netspeed_rx         receive network speed           interface name (wlan0)
 * netspeed_tx         transfer network speed          interface name (wlan0)
 * num_files           number of files in a directory  path
 *                                                     (/home/foo/Inbox/cur)
 * ram_free            free memory in GB               NULL
 * ram_perc            memory usage in percent         NULL
 * ram_total           total memory size in GB         NULL
 * ram_used            used memory in GB               NULL
 * run_command         custom shell command            command (echo foo)
 * swap_free           free swap in GB                 NULL
 * swap_perc           swap usage in percent           NULL
 * swap_total          total swap size in GB           NULL
 * swap_used           used swap in GB                 NULL
 * temp                temperature in degree celsius   sensor file
 *                                                     (/sys/class/thermal/...)
 *                                                     NULL on OpenBSD
 *                                                     thermal zone on FreeBSD
 *                                                     (tz0, tz1, etc.)
 * uid                 UID of current user             NULL
 * up                  interface is running            interface name (eth0)
 * uptime              system uptime                   NULL
 * username            username of current user        NULL
 * vol_perc            OSS/ALSA volume in percent      mixer file (/dev/mixer)
 *                                                     NULL on OpenBSD/FreeBSD
 * wifi_essid          WiFi ESSID                      interface name (wlan0)
 * wifi_perc           WiFi signal in percent          interface name (wlan0)
 */

/*
 * Barcolors format reference:
 *   ^fg(RRGGBB)  - set foreground color
 *   ^bg(RRGGBB)  - set background color
 *   ^fg()        - reset foreground to default
 *   ^bg()        - reset background to default
 *
 * Color palette (Catppuccin-inspired):
 *   94928f - default text (FG_COLOR)
 *   6272a4 - dim/separator/units
 *   a6d189 - green (battery good, memory)
 *   f9e2af - yellow (battery mid, warnings)
 *   e78284 - red (battery low, alerts)
 *   8caaee - blue (cpu, icons)
 *   ca9ee6 - purple (volume)
 *   bd93f9 - mauve (time icon)
 *   e5c890 - peach (disk, temp warm)
 *   94e2d5 - teal (cpu temp cool)
 *   cba6f7 - lavender (date)
 *   7FBBB3 - cyan (day name)
 *
 * Separator: ^fg(6272a4)󱋱
 */

#define SEP  " ^fg(6272a4)󱋱 "
#define FG   "94928f"
#define DIM  "6272a4"

static const struct arg args[] = {
	/* function          format          argument */

	{ run_command, "%s", "$HOME/dotfiles/bin/slstatus/sb-date" },
    // "/home/serhii/dotfiles/bin/dwl/sb-key-layout", 
	{ run_command, "%s", "$HOME/dotfiles/bin/slstatus/sb-volume" },
	{ run_command, "%s", "$HOME/dotfiles/bin/slstatus/sb-battery" },
	{ run_command, "%s", "$HOME/dotfiles/bin/slstatus/sb-memory" },
	{ run_command, "%s", "$HOME/dotfiles/bin/slstatus/sb-cpu-load" },
	{ run_command, "%s", "$HOME/dotfiles/bin/slstatus/sb-cpu-temp" },
	{ run_command, "%s", "$HOME/dotfiles/bin/slstatus/sb-disk" },
	{ run_command, "%s", "$HOME/dotfiles/bin/slstatus/sb-weather" },
};
