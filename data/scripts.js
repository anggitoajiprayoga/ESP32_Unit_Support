window.onload = function() {
    if (typeof window.localStorage === 'undefined' || typeof window.sessionStorage === 'undefined') {
        alert('Your browser does not support HTML5. Try upgrading.');
        return;
    };

    navbarSelect();
    wifiStatic();
    BrokerType();
};

function logoutButton() {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "/logout", true);
    xhr.send();
    setTimeout(function(){ window.open("/logged-out","_self"); }, 1000);
  }
  function rebootButton() {
    document.getElementById("statusdetails").innerHTML = "Invoking Reboot ...";
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "/reboot", true);
    xhr.send();
    window.open("/reboot","_self");
  }
  function listFilesButton() {
    xmlhttp=new XMLHttpRequest();
    xmlhttp.open("GET", "/listfiles", false);
    xmlhttp.send();
    document.getElementById("detailsheader").innerHTML = "<h3>Files<h3>";
    document.getElementById("details").innerHTML = xmlhttp.responseText;
  }
  function downloadDeleteButton(filename, action) {
    var urltocall = "/file?name=" + filename + "&action=" + action;
    xmlhttp=new XMLHttpRequest();
    if (action == "delete") {
      xmlhttp.open("GET", urltocall, false);
      xmlhttp.send();
      document.getElementById("status").innerHTML = xmlhttp.responseText;
      xmlhttp.open("GET", "/listfiles", false);
      xmlhttp.send();
      document.getElementById("details").innerHTML = xmlhttp.responseText;
    }
    if (action == "download") {
      document.getElementById("status").innerHTML = "";
      window.open(urltocall,"_blank");
    }
  }
  function showUploadButtonFancy() {
    document.getElementById("detailsheader").innerHTML = "<h3>Upload File<h3>"
    document.getElementById("status").innerHTML = "";
    var uploadform = "<form method = \"POST\" action = \"/\" enctype=\"multipart/form-data\"><input type=\"file\" name=\"data\"/><input type=\"submit\" name=\"upload\" value=\"Upload\" title = \"Upload File\"></form>"
    document.getElementById("details").innerHTML = uploadform;
    var uploadform =
    "<form id=\"upload_form\" enctype=\"multipart/form-data\" method=\"post\">" +
    "<input type=\"file\" name=\"file1\" id=\"file1\" onchange=\"uploadFile()\"><br>" +
    "<progress id=\"progressBar\" value=\"0\" max=\"100\" style=\"width:300px;\"></progress>" +
    "<h3 id=\"status\"></h3>" +
    "<p id=\"loaded_n_total\"></p>" +
    "</form>";
    document.getElementById("details").innerHTML = uploadform;
  }
  function _(el) {
    return document.getElementById(el);
  }
  function uploadFile() {
    var file = _("file1").files[0];
    // alert(file.name+" | "+file.size+" | "+file.type);
    var formdata = new FormData();
    formdata.append("file1", file);
    var ajax = new XMLHttpRequest();
    ajax.upload.addEventListener("progress", progressHandler, false);
    ajax.addEventListener("load", completeHandler, false); // doesnt appear to ever get called even upon success
    ajax.addEventListener("error", errorHandler, false);
    ajax.addEventListener("abort", abortHandler, false);
    ajax.open("POST", "/");
    ajax.send(formdata);
  }
  function progressHandler(event) {
    //_("loaded_n_total").innerHTML = "Uploaded " + event.loaded + " bytes of " + event.total; // event.total doesnt show accurate total file size
    _("loaded_n_total").innerHTML = "Uploaded " + event.loaded + " bytes";
    var percent = (event.loaded / event.total) * 100;
    _("progressBar").value = Math.round(percent);
    _("status").innerHTML = Math.round(percent) + "% uploaded... please wait";
    if (percent >= 100) {
      _("status").innerHTML = "Please wait, writing file to filesystem";
    }
  }
  function completeHandler(event) {
    _("status").innerHTML = "Upload Complete";
    _("progressBar").value = 0;
    xmlhttp=new XMLHttpRequest();
    xmlhttp.open("GET", "/listfiles", false);
    xmlhttp.send();
    document.getElementById("status").innerHTML = "File Uploaded";
    document.getElementById("detailsheader").innerHTML = "<h3>Files<h3>";
    document.getElementById("details").innerHTML = xmlhttp.responseText;
  }
  function errorHandler(event) {
    _("status").innerHTML = "Upload Failed";
  }
  function abortHandler(event) {
    _("status").innerHTML = "inUpload Aborted";
  }

var navbarSelect = function() {
    var navitem = document.getElementsByClassName('nav-button');
    var navActiv= window.localStorage.getItem('navActiv');

    navActiv = navActiv ? navActiv : 'page-sensor';

    if (navitem.length > 0) {
        for (var i = 0; i < navitem.length; i++) {
            var dataTarget = navitem[i].getAttribute('data-target');

            if (dataTarget == navActiv) {
                menuSelect(document.getElementById(dataTarget));
                selectNav(navitem[i]);
            }

            navitem[i].addEventListener('click', function() {
                var dataTrg = this.getAttribute('data-target');
                if (typeof dataTrg !== 'undefined') {
                    menuSelect(document.getElementById(dataTrg));   
                }
                selectNav(this);
            });
        }
    }
}

var selectNav = function(nav) {
    var data = nav.getAttribute('data-target');
    removeNavSelect();
    nav.classList.add('active');
    
    if (data) {
        var x = document.getElementById(data);
        removeSection();
        x.classList.remove('hide');
        window.localStorage.setItem('navActiv', data);
    }
}

var removeNavSelect = function() {
    var navitem = document.getElementsByClassName('nav-button');

    if (navitem.length > 0) {
        for (var i = 0; i < navitem.length; i++) {
            navitem[i].classList.remove('active');
        }
    }
}

var removeSection = function() {
    var selections = document.getElementsByTagName('section');
    if (selections.length > 0) {
        for (var i = 0; i < selections.length; i++) {
            selections[i].setAttribute('class', 'hide');
        }
    }
}

var menuSelect = function(pagesActive) {
    if (typeof pagesActive !== 'undefined') {
        var menuItem = pagesActive.querySelectorAll('.pure-menu-item');
        var menuActive = window.localStorage.getItem('menuActive');

        if (menuItem.length > 0) {
            menuActive = menuActive ? menuActive : menuItem[0].getAttribute('data-target');
            found = 0;
            for (var i = 0; i < menuItem.length; i++) {
                var dataTarget = menuItem[i].getAttribute('data-target');
                
                if (dataTarget == menuActive && typeof document.getElementById(dataTarget) !== 'undefined') {
                    selectMenu(menuItem[i]);
                    found = 1;
                }

                menuItem[i].addEventListener('click', function() {
                    selectMenu(this);
                });
            }

            if (found < 1) {
                selectMenu(menuItem[0]);
            }
        }
        
    }
}

var selectMenu = function(menu) {
    var dataTarget = menu.getAttribute('data-target');
    removeMenuSelect();
    menu.classList.add('pure-menu-selected');
    if (dataTarget) {
        var x = document.getElementById(dataTarget);
        if (typeof x !== 'undefined') {
            x.classList.remove('hide');
            window.localStorage.setItem('menuActive', dataTarget);   
        }
    }
}

var removeMenuSelect = function() {
    var menuItem = document.getElementsByClassName('pure-menu-item');
    if (menuItem.length > 0) {
        for (var i = 0; i < menuItem.length; i++) {
            var dataTarget = menuItem[i].getAttribute('data-target');
            menuItem[i].classList.remove('pure-menu-selected');

            if (dataTarget) {
                var x = document.getElementById(dataTarget);
                if (typeof x !== 'undefined' && x !== null) {
                    if (!x.classList.contains('hide')) {
                        x.classList.add('hide');
                    }
                }
            }
        }
    }
}

var wifiStatic = function() {
    var ipType = document.getElementById('wlan-wifi-iptype');
    var containerIp = document.getElementById('container-wifi-ipstatic');
    if (typeof ipType !== 'undefined') {
        var valUe = ipType.value;
        if (valUe === 'Statis') {
            containerIp.style.display = 'block';
        } else {
            containerIp.style.display = 'none';
        }
    }
}

var BrokerType = function() {
    var broker_type = document.getElementById('wlan-broker-type');
    var antares = document.getElementById('broker-type-antares');
    var custom = document.getElementById('broker-type-custom');
    if (typeof broker_type !== 'undefined') {
        var valUe = broker_type.value;

        if (valUe === 'antares') {
            antares.style.display = 'block';
        } else {
            antares.style.display = 'none';
        }

        if (valUe === 'custom') {
            custom.style.display = 'block';
        } else {
            custom.style.display = 'none';
        }
    }
}