// Copyright (c) 2013 GitHub, Inc. All rights reserved.
// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATOM_BROWSER_NET_ATOM_URL_REQUEST_URL_REQUEST_JOB_FACTORY_H_
#define ATOM_BROWSER_NET_ATOM_URL_REQUEST_URL_REQUEST_JOB_FACTORY_H_

#include <map>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/synchronization/lock.h"
#include "net/url_request/url_request_job_factory.h"

namespace atom {

class AtomURLRequestJobFactory : public net::URLRequestJobFactory {
 public:
  AtomURLRequestJobFactory();
  virtual ~AtomURLRequestJobFactory();

  // Sets the ProtocolHandler for a scheme. Returns true on success, false on
  // failure (a ProtocolHandler already exists for |scheme|). On success,
  // URLRequestJobFactory takes ownership of |protocol_handler|.
  bool SetProtocolHandler(const std::string& scheme,
                          ProtocolHandler* protocol_handler);

  // Intercepts the ProtocolHandler for a scheme. Returns the original protocol
  // handler on success, otherwise returns NULL.
  ProtocolHandler* ReplaceProtocol(const std::string& scheme,
                                     ProtocolHandler* protocol_handler);

  // Returns the protocol handler registered with scheme.
  ProtocolHandler* GetProtocolHandler(const std::string& scheme) const;

  // Whether the protocol handler is registered by the job factory.
  bool HasProtocolHandler(const std::string& scheme) const;

  // URLRequestJobFactory implementation
  virtual net::URLRequestJob* MaybeCreateJobWithProtocolHandler(
      const std::string& scheme,
      net::URLRequest* request,
      net::NetworkDelegate* network_delegate) const OVERRIDE;
  virtual bool IsHandledProtocol(const std::string& scheme) const OVERRIDE;
  virtual bool IsHandledURL(const GURL& url) const OVERRIDE;

 private:
  typedef std::map<std::string, ProtocolHandler*> ProtocolHandlerMap;

  ProtocolHandlerMap protocol_handler_map_;

  mutable base::Lock lock_;

  DISALLOW_COPY_AND_ASSIGN(AtomURLRequestJobFactory);
};

}  // namespace atom

#endif  // ATOM_BROWSER_NET_ATOM_URL_REQUEST_URL_REQUEST_JOB_FACTORY_H_
