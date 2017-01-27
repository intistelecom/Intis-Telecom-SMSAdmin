# Build RPM configuration for CentOS6

%global repo Intis-Telecom-SMSAdmin

Summary: SmsAdmin is a command line utility for extra sms notifications
Name: smsadmin
Version: 3.0.0
Release: 1.el6
URL: https://github.com/intistelecom/%{repo}
Source: https://github.com/intistelecom/%{repo}/archive/%{version}/%{name}-%{version}.tar.gz
License: MIT
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-buildroot
Group: Utilites
Prefix: /usr

%description
SmsAdmin is a command line utility for Win32 and *Unix like systems.
The main utility purpose is to send extra notifications via sms service.
This utility use only intistele.com service (http://intistele.com/)

%prep
sudo yum install -y curl-devel

%autosetup -n %{repo}-%{version}

%build
cd ./build

cmake ../ \
-DCMAKE_BUILD_WITH_INSTALL_RPATH=ON \
-DCMAKE_INSTALL_PREFIX="%{buildroot}%{_prefix}" \
-DSMSADMIN_MAKE_SHARED=OFF \
-DSMSADMIN_DEFAULT_CONF_FILE=~/smsadmin.cfn \
-DSMSADMIN_DEFAULT_LOG_FILE=~/smsadmin.log

make

%install
cd ./build
%{__make} install PREFIX="%{buildroot}%{_prefix}"

mkdir -p %{buildroot}%{_prefix}/share/doc/smsadmin

install -m 644 %{_builddir}/%{repo}-%{version}/doc/config_json_example.cfn %{buildroot}%{_prefix}/share/doc/smsadmin
install -m 644 %{_builddir}/%{repo}-%{version}/README %{buildroot}%{_prefix}/share/doc/smsadmin
install -m 644 %{_builddir}/%{repo}-%{version}/CHANGELOG %{buildroot}%{_prefix}/share/doc/smsadmin

%pre

%post

%files
%defattr(-,root,root)

%{_bindir}/smsadmin
%{_prefix}/share/doc/smsadmin/config_json_example.cfn
%{_prefix}/share/doc/smsadmin/README
%{_prefix}/share/doc/smsadmin/CHANGELOG

%exclude /usr/include
%exclude /usr/lib
