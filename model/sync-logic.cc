/* -*- Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil -*- */
/*
 * Copyright (c) 2012 University of California, Los Angeles
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Zhenkai Zhu <zhenkai@cs.ucla.edu>
 *         卞超轶 Chaoyi Bian <bcy@pku.edu.cn>
 *	   Alexander Afanasyev <alexander.afanasyev@ucla.edu>
 */

#include "sync-logic.h"

using namespace std;
using namespace boost;

namespace Sync
{

SyncLogic::SyncLogic (const string &syncPrefix,
                      LogicCallback fetch,
                      CcnxWrapperPtr ccnxHandle)
  : m_syncPrefix (syncPrefix)
  , m_fetch (fetch)
  , m_ccnxHandle (ccnxHandle)
{
}

SyncLogic::~SyncLogic ()
{

}

void
SyncLogic::processSyncData (const string &name, const string &dataBuffer)
{

}

void
SyncLogic::addLocalNames (const string &prefix, uint32_t session, uint32_t seq)
{
  NameInfoConstPtr info = StdNameInfo::FindOrCreate(prefix);
  SeqNo seqN(session, seq);
  m_state.update(info, seqN);
}

void
SyncLogic::respondSyncInterest (const string &interest)
{
  string hash = interest.substr(interest.find_last_of("/") + 1);

  Digest digest;

  digest << hash;

}

void
SyncLogic::sendSyncInterest ()
{
  ostringstream os;
  os << m_syncPrefix << "/" << m_state.getDigest();
  
  m_ccnxHandle->sendInterest (os.str (),
                              bind (&SyncLogic::processSyncData, this, _1, _2));
}

}