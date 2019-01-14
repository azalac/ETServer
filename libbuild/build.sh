#!/bin/bash

#downloads a command bin zip, unzips it, and adds its bin folder to the path
#args: 1 - command, 2 - zip download url, 3 - unzipped bin path (can be relative)
function download_command() {
    wget "$2" --output-document "$1.zip" || (echo "Could not download $1 from $2, exiting" && exit 1)
    unzip -u "$1.zip" -d "$1" || (echo "Could not unzip $1.zip, exiting" && exit 1)
    
    pdir="$(realpath $3 || (echo \"Could not determine real path for '$3', exiting\" && exit 1))"
    echo "Adding $pdir to local path"
    export PATH="$pdir:$PATH"
}

#checks if a command exists
#args: 1 - command, 2 - zip download url, 3 - unzipped bin path (can be relative)
function ensure_exists() {

    if ! which "$1" 1>/dev/null 2>/dev/null; then
        export COMMAND_NOT_INSTALLED=1
        
        if [ -e "$3/$1" ]; then
            echo "$1 is not installed, but is downloaded"
            
            pdir="$(realpath $3 || (echo \"Could not determine real path for '$3', exiting\" && exit 1))"
            echo "Adding $pdir to local path"
            export PATH="$pdir:$PATH"
    
            return
        fi
        
        read -r -p "command $1 isn't in your path, download (Y/yes/N/no)? " response
        case "$response" in
            [yY][eE][sS]|[yY])
            download_command "$1" "$2" "$3"
                ;;
            *)
                echo "User chose to not download $1, exiting"
                exit 1
                ;;
        esac
        
    else
        export COMMAND_NOT_INSTALLED=0
        echo "Found command $1, not downloading"
    fi
}


function check_c_lib() {
    echo "Checking for library $1"
    gcc 
}


if ! ensure_exists "autoconf" "https://superb-dca2.dl.sourceforge.net/project/gnuwin32/autoconf/2.63/autoconf-2.63-bin.zip" "autoconf/bin"; then
    exit 1
fi

if [ "$COMMAND_NOT_INSTALLED" = "1" ]; then
    #a fix for autoconf wanting an installed autom4te
    function fake_exec() {
        if [ "$1" = 'c:/progra~1/autoconf/bin/autom4te' ]; then
            shift
            autom4te $@
        else
            builtin exec $@
        fi
    }
    
    export -f fake_exec
    alias 'exec'='fake_exec'
fi

echo "Downloading libxml2 from gitlab"

if ! git clone "https://gitlab.gnome.org/GNOME/libxml2/"; then
    
    if cd libxml2; then
        echo "libxml2 already cloned, attempting to pull latest version"
        git pull
        cd ..
    else
        echo "Could not clone https://gitlab.gnome.org/GNOME/libxml2/, exiting"
        exit 1
    fi
fi

cd libxml2

echo "Configuring autoconf's internal paths"

#find autom4te and escape its path
autom4te_path=$(which autom4te | sed 's|/|\\\/|g')

sed 's|exec "$AUTOM4TE" "$@"|exec \"'$autom4te_path'\" "$@"|g' $(which autoconf) > ./autoconf_config

chmod +x ./autoconf_config

echo "Running autoconf..."

./autoconf_config --verbose






















